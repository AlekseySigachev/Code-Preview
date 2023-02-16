using UnityEngine;
using MainNameSpace.Utils;
using MainNameSpace.components.ColliderBased;
using MainNameSpace.components.GoBased;
using MainNameSpace.components.Health;
using System;

namespace MainNameSpace.Creature.AI 
{
    public class SeashellTrapAI : MonoBehaviour
    {
        [Header("Checkers")]
        [SerializeField] private CheckCircleOverlap _meleeAttack;
        [SerializeField] private ColliderCheck _vision;
        [SerializeField] private ColliderCheck _meleeCanAttack;

        [Header("Cooldown")]
        [SerializeField] private Cooldown _meleeCooldown;
        [SerializeField] private Cooldown _rangeCooldown;

        [Header("Spawner")]
        [SerializeField] private SpawnComponent _rangeAttack;

        private Animator _animator;

        private static readonly int IsDeadKey = Animator.StringToHash("isdead");
        private static readonly int Melee = Animator.StringToHash("bite");
        private static readonly int Range = Animator.StringToHash("fire");

        private void Awake()
        {
            _animator = GetComponent<Animator>();
        }
        private void Update()
        {
            if (_vision.IsTouchingLayer)
                {
                    if (_meleeCanAttack.IsTouchingLayer)
                    {
                        if (_meleeCooldown.IsReady)
                            MeleeAttack();
                        return;
                    }
                    if (_rangeCooldown.IsReady)
                        RangeAttack();
                }
        }

        private void RangeAttack()
        {
            _rangeCooldown.Reset();
            _animator.SetTrigger(Range);
        }

        private void MeleeAttack()
        {
            _meleeCooldown.Reset();
            _animator.SetTrigger(Melee);
        }

        public void OnMeleeAttack()
        {
            _meleeAttack.Check();
        }

        public void OnRangeAttack()
        {
            _rangeAttack.Spawn();
        }
    }
}

