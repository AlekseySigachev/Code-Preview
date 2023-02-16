using System.Collections;
using UnityEngine;
namespace MainNameSpace.Creature.Patroling
{
    public abstract class Patrol : MonoBehaviour
    {
        public abstract IEnumerator DoPatrol();
    }
}
