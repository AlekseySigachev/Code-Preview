using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

namespace MainNameSpace.components.Health


{
    public class HealthComponent : MonoBehaviour
    {

        [SerializeField] private int _health;
        [SerializeField] private UnityEvent _onDamage;
        [SerializeField] private UnityEvent _onHeal;
        [SerializeField] public UnityEvent _onDie;
        [SerializeField] private HealthChangeEvent _onChangeHealth;

        public void ModifyHealth(int healthDelta)
        {
            if (_health <= 0) return;
            _health += healthDelta;
            _onChangeHealth?.Invoke(_health);
            if (healthDelta < 0)
            {
                _onDamage?.Invoke();
            }
            if (healthDelta > 0)
            {
                _onHeal?.Invoke();
            }


            if (_health <= 0)
            {
                _onDie?.Invoke();
            }
            return;
        }


        public void SetHealth(int health)
        {
            _health = health;
        }

        private void OnDestroy()
        {
            _onDie.RemoveAllListeners();
        }

        [Serializable]
        public class HealthChangeEvent : UnityEvent<int>
        {

        }
    }
}

