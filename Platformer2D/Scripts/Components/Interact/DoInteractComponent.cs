using System.Collections;
using System.Collections.Generic;
using UnityEngine;
namespace MainNameSpace.components.interact
{
    public class DoInteractComponent : MonoBehaviour
    {
        public void DoInteraction(GameObject go)
        {
            var interactable = go.GetComponent<InteractableComponent>();
            if(interactable != null)
            {
                interactable.Interact();
            }
        }
    }
}
