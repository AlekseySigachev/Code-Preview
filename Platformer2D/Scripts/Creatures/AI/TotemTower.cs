using MainNameSpace.components.Health;
using MainNameSpace.Utils;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
namespace MainNameSpace.Creature.AI
{
    public class TotemTower : MonoBehaviour
    {
        [SerializeField] private List<ShootingTrapAI> _traps;
        [SerializeField] private Cooldown _cooldown;
        private int _currentTrap;

        private void Start()
        {
            foreach(var trap in _traps)
            {
                trap.enabled = false;
                var hp = trap.GetComponent<HealthComponent>();
                hp._onDie.AddListener( () => OnTrapDead(trap));
            }
        }

        private void OnTrapDead(ShootingTrapAI trap)
        {
            var index = _traps.IndexOf(trap);
            _traps.Remove(trap);
            if (index < _currentTrap) _currentTrap--;
            if(_traps.Count == 0)
            {
                Destroy(gameObject, 0.5f);
            }
        }
        private void Update()
        {
            var hasAnyTarget = _traps.Any(x => x._vision.IsTouchingLayer);
            if (hasAnyTarget)
            {
                if (_cooldown.IsReady)
                {
                    _traps[_currentTrap].Shoot();
                    _cooldown.Reset();
                    _currentTrap = (int) Mathf.Repeat(_currentTrap + 1, _traps.Count);
                }
            }
        }
    }
}
