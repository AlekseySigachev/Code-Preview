using System;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;

namespace MainNameSpace.components
{
    public class ProbobilityDropComponent : MonoBehaviour
    {
        [SerializeField] private int _count;
        [SerializeField] private DropData[] _drop;
        [SerializeField] private DropEvent _onDropCalculated;
        [SerializeField] private bool _spawnOnEnable;
        [ContextMenu("CalculateDrop")]
        private void OnEnable()
        {
            if (_spawnOnEnable) CalculateDrop();
        }
        public void CalculateDrop()
        {
            var itemsToDrop = new GameObject[_count];
            var itemCount = 0;
            var total = _drop.Sum(DropData => DropData.Probability);
            var sortedDrop = _drop.OrderBy(DropData => DropData.Probability);
            

            while (itemCount < _count)
            {
                var random = UnityEngine.Random.value * total;
                var current = 0f;
                foreach (var dropData in sortedDrop)
                {
                    current += dropData.Probability;
                    if(current >= random)
                    {
                        itemsToDrop[itemCount] = dropData.Drop;
                        itemCount++;
                        break;
                    }
                }
            }
            _onDropCalculated?.Invoke(itemsToDrop);

        }
        
        [Serializable]
        public class DropData
        {
            public GameObject Drop;
            [Range(0f, 100f)] public float Probability;
        }

        public void SetCount(int numCoinsToSpawn)
        {
            _count = numCoinsToSpawn;
        }


        [Serializable]
        public class DropEvent : UnityEvent<GameObject[]>
        {

        }
    }
}
