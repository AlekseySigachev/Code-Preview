using MainNameSpace.components.ColliderBased;
using MainNameSpace.components.GoBased;
using MainNameSpace.Creature.Patroling;
using System.Collections;
using UnityEngine;

namespace MainNameSpace.Creature.AI
{
    public class EnemyAI : MonoBehaviour
    {
        [SerializeField] private ColliderCheck _vision;
        [SerializeField] private ColliderCheck _canAttack;
        [SerializeField] private float _alarmDelay;
        [SerializeField] private float _attackCooldown = 1f;
        [SerializeField] private float _missTargetCooldown = 1f;

        private IEnumerator _current;
        private GameObject _target;
        private Creature _creature;
        private bool _isDead;
        private Patrol _patrol;


        private Animator _animator;
        private static readonly int IsDeadKey = Animator.StringToHash("IsDead");
        private static readonly int OnAfterDeadKey = Animator.StringToHash("AfterDeath");

        private SpawnListComponent _particles;

        private void Awake()
        {
            _particles = GetComponent<SpawnListComponent>();
            _creature = GetComponent<Creature>();
            _animator = GetComponent<Animator>();
            _patrol = GetComponent<Patrol>();
        }

        private void Start()
        {
            StartState(_patrol.DoPatrol());
        }

        public void OnHeroInVision(GameObject go)
        {
            if (_isDead) return;
            _target = go;
            StartState(AgroToCharacter());
            
        }

        private IEnumerator AgroToCharacter()
        {
            LookAtHero();
            _particles.Spawn("Exclamation");
            yield return new WaitForSeconds(_alarmDelay);
            StartState(GoToCharacter());
        }

        private Vector2 GetDirectionToTarget()
        {
            var direction = _target.transform.position - transform.position;
            direction.y = 0;
            return direction.normalized;
        }
        private void LookAtHero()
        {
            _creature.SetDirection(Vector2.zero);
            var direction = GetDirectionToTarget();
            _creature.UpdateSpriteDirection(direction);
        }

        private IEnumerator GoToCharacter()
        {
            while (_vision.IsTouchingLayer)
            {
                if(_canAttack.IsTouchingLayer)
                {
                    StartState(Attack());
                }
                else
                {
                    SetDirectionToTarget();
                } 
                
                yield return null;
            }
            _creature.SetDirection(Vector2.zero);
            _particles.Spawn("MissTarget");
            yield return new WaitForSeconds(_missTargetCooldown);
            StartState(_patrol.DoPatrol());
        }

        private IEnumerator Attack()
        {
            while (_canAttack.IsTouchingLayer)
            {
                _creature.Attack();
                _particles.Spawn("Attack");
                yield return new WaitForSeconds(_attackCooldown);
            }
            StartState(GoToCharacter());
        }

        private void SetDirectionToTarget()
        {
            var direction = GetDirectionToTarget();
            _creature.SetDirection(direction);
        }
        private void StartState(IEnumerator coroutine)
        {
            _creature.SetDirection(Vector2.zero);
            if (_current != null) StopCoroutine(_current);

            _current = coroutine;
            StartCoroutine(coroutine);
        }

        public void OnDie()
        {
            _creature.SetDirection(Vector2.zero);
            _isDead = true;
            _animator.SetBool(IsDeadKey, true);
            _particles.Spawn("Dead");
            //_particles.Spawn("DeadBody");
            if (_current != null) StopCoroutine(_current);
            _animator.SetBool(OnAfterDeadKey, true);
        }

    }
}
