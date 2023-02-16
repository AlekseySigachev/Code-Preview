using UnityEngine;
namespace MainNameSpace.components.ColliderBased
{
    public class ColliderCheck : LayerCheck
    {
        private Collider2D _collider;
        private void Awake()
        {
            _collider = GetComponent<Collider2D>();
        }
        private void OnTriggerStay2D(Collider2D collision)
        {
            _IsTouchingLayer = _collider.IsTouchingLayers(_layer);
        }

        private void OnTriggerExit2D(Collider2D collision)
        {
            _IsTouchingLayer = _collider.IsTouchingLayers(_layer);
        }
    }
}

