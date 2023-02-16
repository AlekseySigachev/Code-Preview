using System;
using UnityEngine;
using UnityEngine.Events;
namespace MainNameSpace.components.ColliderBased
{
    public class EnterCollisionComponent : MonoBehaviour
    {
        [SerializeField] private string _tag;
        [SerializeField] private string _AnotherTag;
        [SerializeField] private EnterEvent _action;
        
        private void OnCollisionEnter2D (Collision2D other)
        {
            if (other.gameObject.CompareTag(_tag))
            {
                _action?.Invoke(other.gameObject);
            } else if (!string.IsNullOrEmpty(_AnotherTag) && other.gameObject.CompareTag(_AnotherTag))
            {
                _action?.Invoke(other.gameObject);
            } 
            return;
        }
        [Serializable]
        public class EnterEvent : UnityEvent<GameObject>
            {
                
            }
    }
}