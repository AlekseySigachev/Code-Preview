using UnityEngine;
using MainNameSpace.components.ColliderBased;
using MainNameSpace.components.GoBased;
using MainNameSpace.components.Audio;

namespace MainNameSpace.Creature
{
    public class Creature : MonoBehaviour
    {
        [Header("General Parametrs")]
        [SerializeField] private bool _invertScale;
        [SerializeField] private float speed;
        [SerializeField] protected float JumpForce;
        [SerializeField] private float _jumpForceAfterDamage;
        [SerializeField] protected float SlamDownVelocity;
        [SerializeField] private int _damage;

        [Header("General Checkers")]
        [SerializeField] protected LayerMask GroundLayer;
        [SerializeField] private ColliderCheck _groundCheck;
        [SerializeField] private CheckCircleOverlap _attackRange;

        [SerializeField] protected SpawnListComponent _particles;


        protected Rigidbody2D Rigidbody2D;
        protected Vector2 CurrentDirection;
        protected Animator Animator;
        protected PlaySoundsComponent Sounds;
        protected bool IsGrounded;
        private bool _isJumping;

        private static readonly int IsGroundAnimKey = Animator.StringToHash("IsGround");
        private static readonly int IsRunningAnimKey = Animator.StringToHash("IsRunning");
        private static readonly int VerticalVelocityAnimKey = Animator.StringToHash("VerticalVelocity");
        private static readonly int Hit = Animator.StringToHash("Hit");
        private static readonly int AttackKey = Animator.StringToHash("Attack");

        protected virtual void Awake()
        {
            Rigidbody2D = GetComponent<Rigidbody2D>();
            Animator = GetComponent<Animator>();
            Sounds = GetComponent<PlaySoundsComponent>();
        }

        protected virtual void Update()
        {
            IsGrounded = _groundCheck.IsTouchingLayer;
        }

        private void FixedUpdate()
        {
            var xVelocity = CurrentDirection.x * speed;
            var yVelocity = CalculateYVelocity();
            Rigidbody2D.velocity = new Vector2(xVelocity, yVelocity);

            Animator.SetFloat(VerticalVelocityAnimKey, Rigidbody2D.velocity.y);
            Animator.SetBool(IsRunningAnimKey, CurrentDirection.x != 0);
            Animator.SetBool(IsGroundAnimKey, IsGrounded);

            UpdateSpriteDirection(CurrentDirection);

        }

        public void SetDirection(Vector2 direction)
        {
            CurrentDirection = direction;
        }

        protected virtual float CalculateYVelocity()
        {
            var yVelocity = Rigidbody2D.velocity.y;
            var IsJumpPressing = CurrentDirection.y > 0;

            if (IsGrounded)
            {
                _isJumping = false;
            }

            if (IsJumpPressing)
            {
                _isJumping = true;
                var IsFalling = Rigidbody2D.velocity.y <= 0.001f;
                yVelocity = IsFalling ? CalculateJumpVelocity(yVelocity) : yVelocity;
            }
            else if (Rigidbody2D.velocity.y > 0 && _isJumping)
            {
                yVelocity *= 0.5f;
            }
            return yVelocity;
        }

        protected virtual float CalculateJumpVelocity(float yVelocity)
        {
            if (IsGrounded) yVelocity += JumpForce;
            return yVelocity;
        }
        protected void DoJumpVfs()
        {
            _particles.Spawn("DoubleJump");
            Sounds.Play("Jump");
        }

        public void UpdateSpriteDirection(Vector2 direction)
        {
            var multiplier = _invertScale ? -1 : 1;
            if (direction.x > 0)
            {
                transform.localScale = new Vector3(multiplier, 1, 1);
            }
            else if (direction.x < 0)
            {
                transform.localScale = new Vector3(-1 * multiplier, 1, 1);
            }
        }
        public virtual void TakeDamage()
        {
            _isJumping = false;
            Animator.SetTrigger(Hit);
            Rigidbody2D.velocity = new Vector2(Rigidbody2D.velocity.x, _jumpForceAfterDamage);
        }
        public virtual void Attack()
        {
            Animator.SetTrigger(AttackKey);
            Sounds.Play("Melee");
        }
        public virtual void OnAttackAnimation() //AnimEvent
        {
            _attackRange.Check();
        }
    }
}
