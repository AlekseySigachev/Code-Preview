using System.Collections;
using UnityEngine;

namespace MainNameSpace.Creature.Patroling
{
    public class PatrolPoint : Patrol
    {
        [SerializeField] private Transform[] _points;
        [SerializeField] private float _treshhold = 1f;

        private Creature _creature;
        private int _destinationPointIndex;

        private void Awake()
        {
            _creature = GetComponent<Creature>();
        }
        public override IEnumerator DoPatrol()
        {
            while (enabled)
            {
                if (IsOnPoint())
                {
                    _destinationPointIndex = (int)Mathf.Repeat(_destinationPointIndex + 1, _points.Length);
                }

                var direction = _points[_destinationPointIndex].position - transform.position;
                direction.y = 0;
                _creature.SetDirection(direction.normalized);
                yield return null;
            }
        }

        private bool IsOnPoint()
        {
            return (_points[_destinationPointIndex].position - transform.position).magnitude < _treshhold;
        }
    }
}

