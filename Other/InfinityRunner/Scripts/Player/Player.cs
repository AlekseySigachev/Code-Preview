using UnityEngine;
using UnityEngine.Events;

public class Player : MonoBehaviour
{
    [SerializeField] private int _health;
    public event UnityAction<int> OnHealthChange;
    public event UnityAction OnPlayerDied;

    private void Start()
    {
        OnHealthChange?.Invoke(_health);
    }
    public void ApplyDamage(int damage)
    {
        _health -= damage;
        OnHealthChange?.Invoke(_health);
        if (_health <= 0)
            Die();
    }
    public void Die()
    {
        OnPlayerDied?.Invoke();
    }
}
