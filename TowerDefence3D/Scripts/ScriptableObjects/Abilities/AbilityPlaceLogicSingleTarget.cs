using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(menuName = "Abilities/Place Logic/Single Target")]
public class AbilityPlaceLogicSingleTarget : AbilityPlaceLogic
{
    public override List<Unit> TryGetTargets(Vector3 targetPosition)
    {
        var ray = Camera.main.ScreenPointToRay(targetPosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, 15))
        {
            if (hit.transform.GetComponent<Unit>())
            {
                return new List<Unit>() { hit.transform.GetComponent<Unit>() };
            }
        }
        return null;
    }
}
