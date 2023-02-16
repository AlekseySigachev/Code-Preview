using MainNameSpace.Creature.Character;
using MainNameSpace.Model.Data;
using MainNameSpace.Model.Definitions;
using MainNameSpace.Utils;
using UnityEngine;
namespace MainNameSpace.components.Collectables
{
    public class InventoryAddComponent : MonoBehaviour
    {
        [InventoryIdAttribute] [SerializeField] private string _id;
        [SerializeField] private int _count;

        public void Add(GameObject go)
        {
            var character = go.GetInterface<ICanAddInInventory>();
            character?.AddInInventory(_id, _count);
        }
    }
}

