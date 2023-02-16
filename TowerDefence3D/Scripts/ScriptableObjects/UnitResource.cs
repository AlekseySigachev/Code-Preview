using UnityEngine;

[CreateAssetMenu(menuName = "Units/NewUnit")]
public class UnitResource : ScriptableObject
{
    [SerializeField] private string _name;
    [SerializeField] private int _gold;
    [SerializeField] private int _health;
    [SerializeField] private int _movementSpeed;
    [SerializeField] private GameObject _prefab;

    public string Name => _name;
    public int Health => _health;
    public int MovementSpeed => _movementSpeed;
    public int Gold => _gold;
    public GameObject Prefab => _prefab;

}
