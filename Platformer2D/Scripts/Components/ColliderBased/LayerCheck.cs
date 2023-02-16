using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace MainNameSpace.components.ColliderBased
{
    public class LayerCheck : MonoBehaviour
    {
        [SerializeField] protected LayerMask _layer;
        [SerializeField] protected bool _IsTouchingLayer;
        public bool IsTouchingLayer => _IsTouchingLayer;
    }

}