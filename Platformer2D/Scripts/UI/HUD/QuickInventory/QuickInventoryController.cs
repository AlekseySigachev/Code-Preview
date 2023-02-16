using MainNameSpace.Model;
using MainNameSpace.Model.Data;
using MainNameSpace.Utils.Disposables;
using System;
using System.Collections.Generic;
using UnityEngine;
namespace MainNameSpace.UI.HUD.QuickInventory
{
    public class QuickInventoryController : MonoBehaviour
    {
        [SerializeField] private Transform _container;
        [SerializeField] private InventoryItemWidget _prefab;

        private readonly CompositeDisposable _trash = new CompositeDisposable();
        private GameSession _session;
        private InventoryItemData[] _inventory;
        private List<InventoryItemWidget> _createdItems = new List<InventoryItemWidget>();

        private void Start()
        {
            _session = FindObjectOfType<GameSession>();
            Rebuild();
        }

        private void Rebuild()
        {
            _inventory = _session.data.Inventory.GetAll();
            //create required items
            for (var i = _createdItems.Count; i < _inventory.Length; i++)
            {
                var item = Instantiate(_prefab, _container);
                _createdItems.Add(item);
            }
            //update data and activate
            for (var i = 0; i < _inventory.Length; i++)
            {
                _createdItems[i].SetData(_inventory[i], i);
                _createdItems[i].gameObject.SetActive(true);
            }

            //hide unused items
            for (var i = _inventory.Length; i < _createdItems.Count; i++)
            {
                _createdItems[i].gameObject.SetActive(false);
            }
        }
    }
}