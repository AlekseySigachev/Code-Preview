using UnityEngine;

[RequireComponent(typeof(PlayerMover))]
public class PlayerInput : MonoBehaviour
{
    private PlayerMover _mover;

    private void Start()
    {
        _mover = GetComponent<PlayerMover>();
    }
    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.W)) 
            _mover.TryMoveUp();
        if(Input.GetKeyDown(KeyCode.S)) 
            _mover.TryMoveDown();
    }
}
