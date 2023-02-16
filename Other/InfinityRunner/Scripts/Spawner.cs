using UnityEngine;

public class Spawner : ObjectPool
{
    [SerializeField] private GameObject _enemyPrefab;
    [SerializeField] private Transform[] _spawnPoints;
    [SerializeField] private float _secondBeetweenSpawn;

    private float _elapseTime;
    private void Start()
    {
        Initialize(_enemyPrefab);
    }
    private void Update()
    {
        _elapseTime += Time.deltaTime;
        if(_elapseTime >= _secondBeetweenSpawn)
        {
            if(TryGetObject(out GameObject enemy))
            {
                _elapseTime = 0;
                SetEnemy(enemy, _spawnPoints[GetRandomSpawnPoint()].position);
            }
        }
    }
    private void SetEnemy(GameObject enemy, Vector3 spawnPoint)
    {
        enemy.SetActive(true);
        enemy.transform.position = spawnPoint;
    }
    private int GetRandomSpawnPoint()
    {
        return Random.Range(0, _spawnPoints.Length);
    }
}
