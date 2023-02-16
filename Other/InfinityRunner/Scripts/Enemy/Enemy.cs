using UnityEngine;

public class Enemy : MonoBehaviour
{
    [SerializeField] private int _damage;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.TryGetComponent(out Player player))
        {
            player.ApplyDamage(_damage);
        }
        Die();
    }
    private void Die()
    {
        gameObject.SetActive(false);
    }
}
