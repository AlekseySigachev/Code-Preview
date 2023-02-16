using System.Collections;
using UnityEngine;
using UnityEngine.Events;
using System;
namespace MainNameSpace.components
{
    public class TimerComponent : MonoBehaviour
    {
        [SerializeField] private TimerData[] _timers;
            
        public void SetTimer(int index)
        {
            var timer = _timers[index];

            StartCoroutine(StartTimer(timer));
        }

        private IEnumerator StartTimer(TimerData timer)
        {
            yield return new WaitForSeconds(timer._delay);

            timer.OnTimesUp?.Invoke();
        }

        [Serializable]
        
        public class TimerData
        {
            public float _delay;
            public UnityEvent OnTimesUp;

        }
    }

}