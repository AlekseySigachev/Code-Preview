using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;

public class Tower : MonoBehaviour
{
    [SerializeField] private Transform _partToRotate;

    public UnityAction OnTargetDetected;
    public UnityAction OnTargetConceal;

    private Coroutine _followTargetCoroutine;
    private List<Unit> _targets = new List<Unit>();

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Unit>())
        {
            OnTargetDetected?.Invoke();
            _targets.Add(other.GetComponent<Unit>());

            if (_followTargetCoroutine == null)
                _followTargetCoroutine = StartCoroutine(FollowTarget());
        }
    }
    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<Unit>())
        {
            _targets.Remove(other.GetComponent<Unit>());

            if (!_targets.Any() && _followTargetCoroutine != null)
            {
                OnTargetConceal?.Invoke();
                StopCoroutine(_followTargetCoroutine);
                _followTargetCoroutine = null;
            }
        }
    }

    private Unit FindTarget()
    {
        return _targets.First();
    }

    private void RotateTower(Unit target)
    {
        var direction = (target.transform.position - transform.position).normalized;
        _partToRotate.transform.rotation = Quaternion.Slerp(_partToRotate.transform.rotation, Quaternion.LookRotation(new Vector3(direction.x, direction.y, direction.z)), Time.deltaTime * 10.0f);
    }
    private IEnumerator FollowTarget()
    {
        while (true)
        {
            RotateTower(FindTarget());
            yield return new WaitForFixedUpdate();
        }
    }
}
