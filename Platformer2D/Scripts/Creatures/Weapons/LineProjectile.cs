using UnityEngine;
namespace MainNameSpace.Creature.Weapons
{
    public class LineProjectile : BaseProjectile
    {
        protected override void Start()
        {
            base.Start();
            var force = new Vector2(Direction * _speed, 0);
            Rigidbody.AddForce(force, ForceMode2D.Impulse);
        }




/*        private void FixedUpdate()
        {
            var position = _rigidbody2D.position;
            position.x += _direction * _speed;
            _rigidbody2D.MovePosition(position);
        }*/
    }
}

