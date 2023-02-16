using UnityEngine;
using MainNameSpace.components.ColliderBased;
using MainNameSpace.Utils;
using MainNameSpace.Animation;
using System;

namespace MainNameSpace.Creature.AI
{
    public class ShootingTrapAI : MonoBehaviour
    {
        [Header("Checkers")]
        [SerializeField] public ColliderCheck _vision;

        [Header("Animation")]
        [SerializeField] SpriteAnimation _animation;

        [Header("Cooldown")]
        [SerializeField] private Cooldown _cooldown;

        private void Update()
        {
            if(_vision.IsTouchingLayer && _cooldown.IsReady)
            {
                Shoot();
            }
        }

        public void Shoot()
        {
            _cooldown.Reset();
            _animation.SetClip("StartAttack");
        }
    }
}
