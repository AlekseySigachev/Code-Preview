using UnityEngine;

[RequireComponent(typeof(BulletPool))]
public class Balista : Weapon
{
    [SerializeField] private Transform _attackPosition;
    [SerializeField] private Animator _animator;

    private static readonly int _attackKey = Animator.StringToHash("Attack");
    private static readonly int _stopAttackKey = Animator.StringToHash("StopAttack");

    private BulletPool _bulletPool;
    private Bullet _bullet;

    private void Start()
    {
        _bulletPool = GetComponent<BulletPool>();
    }

    protected override void OnAttack()
    {
        _animator.SetTrigger(_attackKey);
    }

    private void AttackAnimEvent()
    {
        _bullet = _bulletPool.TryGetBullet().GetComponent<Bullet>();
        _bullet.gameObject.SetActive(true);
        _bullet.transform.position = _attackPosition.position;
        _bullet.SetTarget(_target);
    }
}
