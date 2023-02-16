using UnityEngine;
using UnityEngine.Events;

public class Unit : MonoBehaviour
{
    [SerializeField] private UnitResource _unitResource;

    public UnityEvent<int> OnUnitDie;

    private string _name;
    private int _health;
    private int _movementSpeed;
    private int _gold;

    public int MovementSpeed => _movementSpeed;

    public void Start()
    {
        _name = _unitResource.Name;
        _health = _unitResource.Health;
        _movementSpeed = _unitResource.MovementSpeed;
        _gold = _unitResource.Gold;
    }

    private void Die()
    {
        gameObject.SetActive(false);
        OnUnitDie?.Invoke(_gold);
    }
    public void ApplyDamage(int damage)
    {
        _health -= damage;
        if (_health <= 0)
            Die();
    }
}
