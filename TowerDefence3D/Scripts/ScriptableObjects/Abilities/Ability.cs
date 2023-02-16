using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Abilities/NewAbility")]
public class Ability : ScriptableObject
{
    [SerializeField] private AbilityPlaceLogic _placeLogic;
    [SerializeField] private List<AbilityAction> _abilityActions;

    public void ApplyAction(List<Unit> targets)
    {
        foreach (AbilityAction action in _abilityActions)
        {
            foreach (Unit target in targets)
            {
                action.Action(target);
            }
        }
    }
    public List<Unit> SelectTargets(Vector3 targetPosition)
    {
        return _placeLogic.TryGetTargets(targetPosition);
    }
}
