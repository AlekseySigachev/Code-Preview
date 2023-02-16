using UnityEngine;

[CreateAssetMenu(menuName = "Waves/New Wave")]
public class Wave : ScriptableObject
{
    [SerializeField] private UnitResource _enemy;
    [SerializeField] private int _enemyQuantity;

    public GameObject UnitTemplate => _enemy.Prefab;
    public int EnemyQuantity => _enemyQuantity;
}
