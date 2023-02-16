using MainNameSpace.Model.Data;
using MainNameSpace.Model.Data.Properties;
using MainNameSpace.Model.Definitions;
using UnityEngine;
namespace MainNameSpace.Model
{
    public class QuickInventoryModel
    {
        private readonly PlayerData _data;
        public InventoryItemData[] Inventory { get; private set; }

        public readonly IntProperty SelectedIndex = new IntProperty();
        public QuickInventoryModel(PlayerData data)
        {
            _data = data;
            Inventory = _data.Inventory.GetAll(ItemTag.Usable);
            data.Inventory.OnChanged += OnInventoryChanged;
        }

        private void OnInventoryChanged(string id, int value)
        {

            Inventory = _data.Inventory.GetAll();
            SelectedIndex.Value = Mathf.Clamp(SelectedIndex.Value, 0, Inventory.Length - 1);
        }
    }
}