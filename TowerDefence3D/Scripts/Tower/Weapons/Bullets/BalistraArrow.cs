using UnityEngine;

public class BalistraArrow : Bullet
{
    [SerializeField] private int _damage;
    protected override void DamageUnit(Unit unit)
    {
        unit.ApplyDamage(_damage);
        gameObject.SetActive(false);
    }
}
