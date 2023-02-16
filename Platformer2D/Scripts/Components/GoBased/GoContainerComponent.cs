using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace MainNameSpace.components.GoBased
{
    public class GoContainerComponent : MonoBehaviour
    {
        [SerializeField] private GameObject[] _gos;
        [SerializeField] private ProbobilityDropComponent.DropEvent _onDrop;

        [ContextMenu("Drop")]
        public void Drop()
        {
            _onDrop?.Invoke(_gos);
        }
    }
}

