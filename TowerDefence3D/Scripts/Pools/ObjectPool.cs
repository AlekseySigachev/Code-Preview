using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class ObjectPool : MonoBehaviour
{
    [SerializeField] private GameObject _objectPoolContainer;
    [SerializeField] private int _quanity;

    private List<GameObject> _pool = new List<GameObject>();

    protected void Init(GameObject prefab)
    {
        for (int i = 0; i < _quanity; i++)
        {
            GameObject spawned = Instantiate(prefab, _objectPoolContainer.transform);
            spawned.SetActive(false);

            _pool.Add(spawned);
        }
    }

    protected bool TryGetObject(out GameObject result, GameObject Prefab)
    {
        result = _pool.FirstOrDefault(go => go.activeSelf == false && go.name == (Prefab.name + "(Clone)"));
        return result != null;
    }

}
