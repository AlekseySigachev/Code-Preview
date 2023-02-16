using System.Collections;
using UnityEngine;

[RequireComponent(typeof(Tower))]

public class Gun : MonoBehaviour
{
    [SerializeField] private Cooldown _attackCooldown;

    private Tower _tower;
    private Coroutine _coolDownCoroutine;

    private void Awake()
    {
        _tower = GetComponent<Tower>();
    }
    private void OnEnable()
    {
        _tower.OnTargetDetected += StartAttack;
        _tower.OnTargetConceal += StopAttack;
    }
    private void StartAttack()
    {
        if (_coolDownCoroutine == null)
            _coolDownCoroutine = StartCoroutine(Attacking());
    }
    private void StopAttack()
    {
        if (_coolDownCoroutine != null)
        {
            StopCoroutine(_coolDownCoroutine);
            _coolDownCoroutine = null;
        }
    }
    private void Attack()
    {
        Debug.Log("Attacking");
    }
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
                Attack();
                _attackCooldown.Reset();
            }
            yield return new WaitForFixedUpdate();
        }
    }
}
