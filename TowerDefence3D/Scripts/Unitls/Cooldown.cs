using System;
using UnityEngine;

[Serializable]
public class Cooldown
{
    [SerializeField] private float _coolDownTime;

    private float _timesUp;

    public void Reset()
    {
        _timesUp = Time.time + _coolDownTime;
    }
    public bool IsReady => _timesUp <= Time.time;
}
