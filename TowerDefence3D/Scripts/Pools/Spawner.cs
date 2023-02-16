using System.Collections;
using UnityEngine;

public class Spawner : ObjectPool
{
    [SerializeField] private Wave[] _waves;
    [SerializeField] private int _timeToStartWaves;
    [SerializeField] private float _timeBetweenWaves;
    [SerializeField] private float _timeBetweenSpawn;

    private void Start()
    {
        foreach (var wave in _waves)
        {
            Init(wave.UnitTemplate);
            Debug.Log(wave.UnitTemplate.name);
        }

        StartCoroutine(StartGame());
    }
    private void SetEnemy(GameObject Unit, Vector3 SpawnPoint)
    {
        Unit.SetActive(true);
        Unit.transform.position = SpawnPoint;
    }

    private IEnumerator StartGame()
    {
        yield return new WaitForSeconds(_timeToStartWaves);
        foreach (var wave in _waves)
        {
            for (int i = 0; i < wave.EnemyQuantity; i++)
            {
                if (TryGetObject(out GameObject Unit, wave.UnitTemplate))
                    SetEnemy(Unit, transform.position);
                yield return new WaitForSeconds(_timeBetweenSpawn);
            }

            yield return new WaitForSeconds(_timeBetweenWaves);
        }
    }
}
