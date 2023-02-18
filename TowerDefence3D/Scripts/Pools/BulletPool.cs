using UnityEngine;

public class BulletPool : ObjectPool
{
    [SerializeField] private GameObject _prefab;

    private void Start()
    {
        Init(_prefab);
    }
    public GameObject TryGetBullet()
    {
        if (TryGetObject(out GameObject Bullet, _prefab))
        {
            return Bullet;
        }
        return null;
    }
}
