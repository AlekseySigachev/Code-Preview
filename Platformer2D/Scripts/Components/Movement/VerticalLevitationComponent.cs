using UnityEngine;
namespace MainNameSpace.components.movement
{
    public class VerticalLevitationComponent : MonoBehaviour
    {
        [SerializeField] private float _frequensy = 1f;
        [SerializeField] private float _amplitude = 1f;
        [SerializeField] private bool _randomize;
        private float _originalY;
        private Rigidbody2D _rigidbody;
        private float _seed;

        private void Awake()
        {
            _rigidbody = GetComponent<Rigidbody2D>();
            _originalY = _rigidbody.position.y;
            if (_randomize)
                _seed = Random.value * Mathf.PI * 2;
        }

        private void Update()
        {
            var position = _rigidbody.position;
            position.y = (_originalY + Mathf.Sin(_seed + Time.time * _frequensy) * _amplitude);
            _rigidbody.MovePosition(position);
        }
    }
}
