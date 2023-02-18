using UnityEngine;

public abstract class Bullet : MonoBehaviour
{
    private Transform _target;
    private float _speed = 30f;

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Unit>())
        {
            DamageUnit(other.gameObject.GetComponent<Unit>());
        }
    }
    protected abstract void DamageUnit(Unit unit);

    public void SetTarget(Transform target)
    {
        _target = target;
    }

    private void FixedUpdate()
    {
        if (_target == null)
        {
            gameObject.SetActive(false);
            return;
        }
        MoveBullet();
        RotateBullet();
    }

    private void MoveBullet()
    {
        transform.position = Vector3.MoveTowards(transform.position, _target.position, _speed * Time.deltaTime);
    }

    private void RotateBullet() 
    {
        Vector3 direction = _target.position - transform.position;
        transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(direction), Time.deltaTime * 10.0f);
    }
}
