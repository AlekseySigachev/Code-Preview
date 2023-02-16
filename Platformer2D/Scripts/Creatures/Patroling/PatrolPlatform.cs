using MainNameSpace.components.ColliderBased;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace MainNameSpace.Creature.Patroling
{
    public class PatrolPlatform : Patrol
    {
        [SerializeField] private LayerCheck _groundCheck;
        [SerializeField] private LayerCheck _obstacleCheck;
        [SerializeField] private int _direction;
        [SerializeField] private Creature _creature;
        public override IEnumerator DoPatrol()
        {
            while (enabled)
            {
                if (_groundCheck.IsTouchingLayer && !_obstacleCheck.IsTouchingLayer)
                {
                    _creature.SetDirection(new Vector2(_direction, 0));
                }
                else
                {
                    _direction = -_direction;
                    _creature.SetDirection(new Vector2(_direction, 0));
                }
                yield return null;
            }
        }
    }
}
