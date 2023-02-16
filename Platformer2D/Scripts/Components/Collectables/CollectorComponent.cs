using MainNameSpace.Model;
using MainNameSpace.Utils;
using MainNameSpace.components.ColliderBased;
using MainNameSpace.components.Health;
using UnityEngine;
using UnityEditor.Animations;
using System.Collections;
using MainNameSpace.components;
using MainNameSpace.Model.Data;
using System.Collections.Generic;

namespace MainNameSpace.components.Collectables
{
    public class CollectorComponent : MonoBehaviour, ICanAddInInventory
    {
        [SerializeField] private List<InventoryItemData> _items = new List<InventoryItemData>();
        public void AddInInventory(string id, int value)
        {
            _items.Add(new InventoryItemData(id) {Value = value });
        }

        public void DropInInventory()
        {
            var session = FindObjectOfType<GameSession>();
            foreach (var InventoryItemData in _items)
            {
                session.data.Inventory.Add(InventoryItemData.Id, InventoryItemData.Value);
            }
            _items.Clear();
        }
    }
}

