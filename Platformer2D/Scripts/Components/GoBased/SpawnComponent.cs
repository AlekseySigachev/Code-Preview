using MainNameSpace.Utils;
using UnityEngine;
namespace MainNameSpace.components.GoBased
{
    public class SpawnComponent : MonoBehaviour
    {
        [SerializeField] private Transform _target;
        [SerializeField] private GameObject _prefab;
        [SerializeField] private bool _invertXScale;

        [ContextMenu("Spawn")] 
        public void Spawn()
        {
            var instantiate = SpawnUtils.Spawn(_prefab, _target.position);
            var scale = _target.lossyScale;
            scale.x *= _invertXScale ? -1 : 1;
            instantiate.transform.localScale = scale;
            instantiate.SetActive(true);
        }

    }
}
