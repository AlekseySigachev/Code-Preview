using UnityEngine;
[CreateAssetMenu(menuName = "Abilities/Actions/Damage")]
public class AbilityActionDamage : AbilityAction
{
    [SerializeField] private int _damage;
    public override void Action(Unit target)
    {
        target.ApplyDamage(_damage);
    }
}
