using UnityEngine;
using Cinemachine;
namespace MainNameSpace.components.CutScenes
{
    public class CameraStateController : MonoBehaviour
    {
        [SerializeField] private Animator _animator;
        [SerializeField] private CinemachineVirtualCamera _camera;

        private static readonly int ShowTargetKey = Animator.StringToHash("ShowTarget");

        public void SetPosition(Vector3 TargetPosition)
        {
            TargetPosition.z = _camera.transform.position.z;
            _camera.transform.position = TargetPosition;
        }

        public void SetState(bool state)
        {
            _animator.SetBool(ShowTargetKey, state);
        }
    }

}