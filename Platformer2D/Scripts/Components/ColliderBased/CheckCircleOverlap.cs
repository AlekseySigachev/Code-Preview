using UnityEngine;
using UnityEditor;
using System;
using UnityEngine.Events;
using System.Linq;

namespace MainNameSpace.components.ColliderBased
{
    public class CheckCircleOverlap : MonoBehaviour
    {
        [SerializeField] private float _radius = 1f;
        [SerializeField] private LayerMask _mask;
        [SerializeField] private OnOverlapEvent _onOverlap;
        [SerializeField] private string[] _tags;


        private Collider2D[] _interactionResult = new Collider2D[10];
        private void OnDrawGizmosSelected()
        {
            Handles.color = HandlesUtils.TransporentRed;
            Handles.DrawSolidDisc(transform.position, Vector3.forward, _radius);
        }

        public void Check()
        {
            var size = Physics2D.OverlapCircleNonAlloc
            (transform.position,
            _radius,
            _interactionResult,
            _mask);

            for (var i = 0; i < size; i++)
            {
                var overlapResult = _interactionResult[i];
                var IsInTag = _tags.Any(tag => overlapResult.CompareTag(tag));
                if (IsInTag)
                {
                    _onOverlap?.Invoke(overlapResult.gameObject);
                }
            }
        }

        [Serializable]
        public class OnOverlapEvent : UnityEvent<GameObject>
        {

        }
    }
}

