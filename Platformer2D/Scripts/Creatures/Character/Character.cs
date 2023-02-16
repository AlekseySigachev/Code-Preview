using MainNameSpace.Model;
using MainNameSpace.Utils;
using MainNameSpace.components.ColliderBased;
using MainNameSpace.components.Health;
using UnityEngine;
using UnityEditor.Animations;
using System.Collections;
using MainNameSpace.components;
using MainNameSpace.Model.Data;

namespace MainNameSpace.Creature.Character
{
    public class Character : Creature, ICanAddInInventory
    {
       // [SerializeField] private LayerCheck _groundCheck;
        [Header("Personal Checkers")]
        [SerializeField] private Vector3 _groundCheckPositionDelta;
        [SerializeField] private float _groundCheckRadius;
        [SerializeField] private ColliderCheck _wallCheck;

        [Space]
        [Header("Personal Interaction")]
        [SerializeField] private CheckCircleOverlap _interactionCheck;
        [SerializeField] private LayerMask _interactLayer;
        [SerializeField] private float _interactionRadius;

        [Space]
        [Header("Personal WeaponParams")]
        [SerializeField] private AnimatorController _armedAnimController;
        [SerializeField] private AnimatorController _disArmedAnimContoller;

        [Header("Throw")]
        [SerializeField] private Cooldown _throwCooldown;
        [Header("Super Throw")]
        [SerializeField] Cooldown _superThrowCooldown;
        [SerializeField] private int _superThrowParticles;
        [SerializeField] private float _superThrowDelay;

        [SerializeField] private ProbobilityDropComponent _hitDrop;

        private bool _allowDoubleJump;
        private bool _superThrow;
        private GameSession _session;
        private bool _isOnWall;
        private float _defalutGravityScale;
        private HealthComponent _health;

        private static readonly int ThrowAttackKey = Animator.StringToHash("ThrowSword");
        private static readonly int IsOnWallKey = Animator.StringToHash("IsOnWall");
        private int CoinsCount => _session.data.Inventory.Count("Coin");
        private int SwordCount => _session.data.Inventory.Count("Sword");

        protected override void Awake()
        {
            base.Awake();
            _defalutGravityScale = Rigidbody2D.gravityScale;
        }

        private void Start()
        {
            _session = FindObjectOfType<GameSession>();
            _health = GetComponent<HealthComponent>();
            _health.SetHealth(_session.data.Health.Value);
            _session.data.Inventory.OnChanged += OnInventoryChanged;
            UpdateHeroWeapon();
        }

        private void OnInventoryChanged(string id, int value)
        {
            if (id == "Sword") UpdateHeroWeapon();
        }

        protected override void Update()
        {
            base.Update();
            var moveToSameDirection = CurrentDirection.x * transform.lossyScale.x > 0;
            if (_wallCheck.IsTouchingLayer && moveToSameDirection)
            {
                _isOnWall = true;
                Rigidbody2D.gravityScale = 2;
            }
            else
            {
                _isOnWall = false;
                Rigidbody2D.gravityScale = _defalutGravityScale;
            }

            Animator.SetBool(IsOnWallKey, _isOnWall);
        }
        public void OnHealthChanged(int currentHealth)
        {
            _session.data.Health.Value = currentHealth;
        }

        protected override float CalculateYVelocity()
        {
            var yVelocity = Rigidbody2D.velocity.y;
            var IsJumpPressing = CurrentDirection.y > 0;

            if (IsGrounded)
            {
                _allowDoubleJump = true;
            }

            if (!IsJumpPressing && _isOnWall)
            {
                return 0f;
            }
            return base.CalculateYVelocity();
        }

        protected override float CalculateJumpVelocity(float yVelocity)
        {
        if (!IsGrounded && _allowDoubleJump)
            {
                DoJumpVfs();
                _allowDoubleJump = false;
                return JumpForce;
            }

            return base.CalculateJumpVelocity(yVelocity);
        }

        public void AddInInventory(string id, int value)
        {
            _session.data.Inventory.Add(id, value);
        }
        public override void TakeDamage()
        {
            base.TakeDamage();
            if (CoinsCount > 0) SpawnCoins();
        }
        public void Heal()
        {
//
        }
        private void SpawnCoins()
        {
            var numCoinsToSpawn = Mathf.Min(CoinsCount, 5);
            _session.data.Inventory.Remove("Coin", numCoinsToSpawn);
            _hitDrop.SetCount(numCoinsToSpawn);
            _hitDrop.CalculateDrop();
        }

        public void Interact()
        {
            _interactionCheck.Check();
        }
        private void OnCollisionEnter2D(Collision2D other)
        {
            if (other.gameObject.IsInLayer(GroundLayer))
            {
                var contact = other.contacts[0];
                if(contact.relativeVelocity.y >= SlamDownVelocity)
                {
                    _particles.Spawn("SlamDown");
                }
/*                //FallDamage        if (contact.relativeVelocity.y >= _slamDownVelocity)
                {
                    GetComponent<HealthComponent>().ModifyHealth(-1);
                }*/
            }

        }
        public override void Attack()
        {
            if (SwordCount <= 0) return;
            base.Attack();
            _particles.Spawn("SwordAttackParticle");
            Debug.Log($"Melee Attack");

        }

        private void UpdateHeroWeapon()
        {
            Animator.runtimeAnimatorController = SwordCount > 0 ? _armedAnimController : _disArmedAnimContoller;
        }

        public void OnThrowAttack()
        {
            if ((SwordCount <= 1)) return;
            if (_superThrow)
            {
                var numThrows = Mathf.Min(_superThrowParticles, SwordCount - 1);
                StartCoroutine(DoSuperThrow(numThrows));
            }
            else
            {
                ThrowAndRemoveFromInventory(1);
            }
            _superThrow = false;
        }

        private IEnumerator DoSuperThrow(int numThrows)
        {
            for (int i = 0; i < numThrows; i++)
            {
                ThrowAndRemoveFromInventory(1);
                yield return new WaitForSeconds(_superThrowDelay);
            }
        }

        private void ThrowAndRemoveFromInventory(int count)
        {
            if ((SwordCount <= 1)) return;
            Sounds.Play("Range");
            _session.data.Inventory.Remove("Sword", count);
            _particles.Spawn("ThrowSword");
        }

        public void StartThrowingThrow()
        {
            if ((SwordCount <= 1)) return;
            _superThrowCooldown.Reset();
        }

        public void PerformThrowing()
        {
            if(!_throwCooldown.IsReady || SwordCount <= 1) return;

            if (_superThrowCooldown.IsReady) _superThrow = true;

            Animator.SetTrigger(ThrowAttackKey);
            _throwCooldown.Reset();

        }

        public void UseHealthPotion()
        {
            var potionName = "HealthPotion";
            var potionsCount = _session.data.Inventory.Count(potionName);
            if(potionsCount > 0)
            {
                _health.ModifyHealth(5);
                _session.data.Inventory.Remove(potionName, 1);
            }
 
        }
        private void OnDestroy()
        {
            if(_session != null) _session.data.Inventory.OnChanged -= OnInventoryChanged;
        }
    }

}

