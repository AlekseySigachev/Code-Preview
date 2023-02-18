using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;

public class Tower : MonoBehaviour
{
    [SerializeField] private Transform _partToRotate;

    public UnityAction<Transform> OnTargetDetected;
    public UnityAction OnTargetConceal;

    private Coroutine _followTargetCoroutine;
    private List<Unit> _targets = new List<Unit>();

    private void OnTriggerEnter(Collider other)
    {
        Unit unit = other.GetComponent<Unit>();
        if (unit)
        {
            _targets.Add(unit);

            if (_followTargetCoroutine == null)
                _followTargetCoroutine = StartCoroutine(FollowTarget());
        }
    }

    private void OnTriggerExit(Collider other)
    {
        Unit unit = other.GetComponent<Unit>();
        if (unit)
        {
            _targets.Remove(unit);

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

    private bool IsUnitAlife(Unit unit)
    {
        return unit.gameObject.activeSelf;
    }

    private void RotateTower(Unit target)
    {
        var direction = (target.transform.position - transform.position).normalized;
        _partToRotate.transform.rotation = Quaternion.Slerp(_partToRotate.transform.rotation, Quaternion.LookRotation(direction), Time.deltaTime * 10.0f);
    }

    private IEnumerator FollowTarget()
    {
        while (true)
        {
            var target = FindTarget();
            if (IsUnitAlife(target))
            {
                RotateTower(target);
                OnTargetDetected?.Invoke(target.transform);
            }
            else
            {
                _targets.Remove(target);
            }
            yield return new WaitForFixedUpdate();
        }
    }
}
