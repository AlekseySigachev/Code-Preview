using MainNameSpace.Model;
using MainNameSpace.Model.Data;
using MainNameSpace.Model.Definitions;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

namespace MainNameSpace.components.interact
{
    public class RequireItemComponent : MonoBehaviour
    {
        [SerializeField] private InventoryItemData[] _requiered;
        [SerializeField] private bool _removeAfterUse;

        [SerializeField] private UnityEvent _onSuccess;
        [SerializeField] private UnityEvent _onFail;
        public void Check()
       {
            var session = FindObjectOfType<GameSession>();
            var areAllRequierementsMet = true;
            foreach ( var item in _requiered)
            {
                var numItems = session.data.Inventory.Count(item.Id);
                if (numItems < item.Value) areAllRequierementsMet = false;
            }
            
            if(areAllRequierementsMet)
            {
                if (_removeAfterUse)
                {
                    foreach (var item in _requiered)
                    {
                        session.data.Inventory.Remove(item.Id, item.Value);
                    }
                }
                _onSuccess?.Invoke();
            }
            else
            {
                _onFail?.Invoke();
            }
        }
    }
}
