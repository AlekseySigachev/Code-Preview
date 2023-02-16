using UnityEngine;
using UnityEngine.InputSystem;
namespace MainNameSpace.Creature.Character
{
    public class InputManager : MonoBehaviour
    {
        [SerializeField] private Character CharacterREF;

        private CharacterInput CharacterMovement;
       
        public void OnHorizontalMovement(InputAction.CallbackContext context)
        {
            var direction = context.ReadValue<Vector2>();
            CharacterREF.SetDirection(direction);
        }

        public void OnInteract(InputAction.CallbackContext context)
        {
            if (context.performed)
            {
                CharacterREF.Interact();
            }
        }
        public void OnAttack(InputAction.CallbackContext context)
        {
            if (context.started)
            {
                CharacterREF.Attack();
            }
        }
        public void OnThrow(InputAction.CallbackContext context)
        {
            if (context.started)
            {
                CharacterREF.StartThrowingThrow();
            }
            if (context.canceled)
            {
                CharacterREF.PerformThrowing();
            }
        }

        public void OnUseHealthPotion(InputAction.CallbackContext context)
        {
            if (context.performed)
            {
                CharacterREF.UseHealthPotion();
            }
        }

    }
}
