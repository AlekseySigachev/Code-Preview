using UnityEngine;

public class PipeGenerator : ObjectPool
{
    [SerializeField] private GameObject _template;
    [SerializeField] private float _secondsBetweenSpawn;
    [SerializeField] private float _maxSpawnPositionY;
    [SerializeField] private float _minSpawnPositionY;

    private float _elapseTime = 0;
    private void Start()
    {
        Initialize(_template);
    }
    private void Update()
    {
        _elapseTime += Time.deltaTime;
        if(_elapseTime > _secondsBetweenSpawn)
        {
            if(TryGetObject(out GameObject pipe))
            {
                _elapseTime = 0;

                float spawnPositionY = Random.Range(_minSpawnPositionY, _maxSpawnPositionY);
                Vector3 spawnPoint = new Vector3(transform.position.x, spawnPositionY, transform.position.z);
                pipe.SetActive(true);
                pipe.transform.position = spawnPoint;

                DisableObjectAbroadScreen();
            }
        }
    }
}
