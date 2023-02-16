using UnityEngine;
namespace MainNameSpace.Creature.Weapons
{
    public class SinusoidalProjectile : BaseProjectile
    {
        [SerializeField] private float _frequensy = 1f;
        [SerializeField] private float _amplitude = 1f;
        private float _originalY;
        private float _time;
        protected override void Start()
        {
            base.Start();
            _originalY = Rigidbody.position.y;
        }

        private void FixedUpdate()
        {
            var position = Rigidbody.position;
            position.x += Direction * _speed;
            position.y = (_originalY + Mathf.Sin(_time * _frequensy)* _amplitude);
            Rigidbody.MovePosition(position);
            _time += Time.fixedDeltaTime;
        }
    }
}

