using UnityEngine;

namespace MainNameSpace.components.Health
{
    public class ModifyHealthComponent : MonoBehaviour
    {
        [SerializeField] private int _hpDelta;

        public void Apply(GameObject target)
        {
            var healthcomponent = target.GetComponent<HealthComponent>();
            if (healthcomponent != null)
            {
                healthcomponent.ModifyHealth(_hpDelta);
            }
        }
    }

}

