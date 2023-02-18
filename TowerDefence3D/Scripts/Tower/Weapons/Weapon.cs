using System.Collections;
using UnityEngine;

public abstract class Weapon : MonoBehaviour
{
    [SerializeField] private Cooldown _attackCooldown;
    [SerializeField] private Tower _tower;

    protected Transform _target;

    private Coroutine _coolDownCoroutine;

    private void OnEnable()
    {
        _tower.OnTargetDetected += StartAttack;
        _tower.OnTargetConceal += StopAttack;
    }
    private void StartAttack(Transform target)
    {
        _target = target;
        if (_coolDownCoroutine == null)
            _coolDownCoroutine = StartCoroutine(Attacking());
    }
    private void StopAttack()
    {
        _target = null;
        if (_coolDownCoroutine != null)
        {
            StopCoroutine(_coolDownCoroutine);
            _coolDownCoroutine = null;
        }
    }
    protected abstract void OnAttack();
    private void OnDisable()
    {
        _tower.OnTargetDetected -= StartAttack;
        _tower.OnTargetConceal -= StopAttack;
    }
    private IEnumerator Attacking()
    {
        while (true)
        {
            if (_attackCooldown.IsReady)
            {
                OnAttack();
                _attackCooldown.Reset();
            }
            yield return new WaitForFixedUpdate();
        }
    }
}
