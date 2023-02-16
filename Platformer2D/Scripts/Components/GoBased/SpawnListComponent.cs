using System;
using System.Linq;
using UnityEngine;
namespace MainNameSpace.components.GoBased
{
    public class SpawnListComponent : MonoBehaviour
    {
        [SerializeField] SpawnData[] _spawners;
        public void SpawnAll()
        {
            foreach (var spawnData in _spawners)
            {
                spawnData.Component.Spawn();
            }
        }

        public void Spawn(string id)
        {
            var spawner = _spawners.FirstOrDefault(arrayElem => arrayElem.id == id);
            spawner?.Component.Spawn();
        }

        [Serializable]
        public class SpawnData
        {
            public string id;
            public SpawnComponent Component;
        }

    }

}
