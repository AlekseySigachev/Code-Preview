using System.Collections;
using UnityEngine;
using UnityEditor;
using Random = UnityEngine.Random;
using MainNameSpace.Utils;

namespace MainNameSpace.components.GoBased
{
    public class RandomSpawner : MonoBehaviour
    {
        [Header("Spawn bound:")]
        [SerializeField] private float _sectorAngle = 60;

        [SerializeField] private float _sectorRotation;

        [Header("Spawn params")]
        [Space]
        [SerializeField] private float _waitTime = 0.1f;
        [SerializeField] private float _speed = 6;

        private Coroutine _routine;

       
        public void StartDrop(GameObject[] items)
        {
            TryStopRoutine();
            _routine = StartCoroutine(StartSpawn(items));
        }

        public void DropImmidiate(GameObject[] items)
        {
            foreach (var item in items)
            {
                Spawn(item);
            }
        }

        private IEnumerator StartSpawn(GameObject[] particles)
        {
            for (var i = 0; i < particles.Length; i++)
            {
                Spawn(particles[i]);

                yield return new WaitForSeconds(_waitTime);
            }
        }

        private void Spawn(GameObject particle)
        {
            var instance = SpawnUtils.Spawn(particle, transform.position);
            var rigidbody = instance.GetComponent<Rigidbody2D>();

            var randomAngle = Random.Range(0, _sectorAngle);
            var forceVector = AngleToVectorInSector(randomAngle);
            rigidbody.AddForce(forceVector * _speed, ForceMode2D.Impulse);
        }

        private void OnDrawGizmosSelected()
        {
            var position = transform.position;

            var middleAngleDelta = (180 - _sectorRotation - _sectorAngle) / 2;
            var rightBound = GetUnitOnCircle(middleAngleDelta);
            Handles.DrawLine(position, position + rightBound);

            var leftBound = GetUnitOnCircle(middleAngleDelta + _sectorAngle);
            Handles.DrawLine(position, position + leftBound);
            Handles.DrawWireArc(position, Vector3.forward, rightBound, _sectorAngle, 1);
            Handles.color = new Color(1f, 1f, 1f, 0.1f);
            Handles.DrawSolidArc(position, Vector3.forward, rightBound, _sectorAngle, 1);
        }

        private Vector2 AngleToVectorInSector(float angle)
        {
            var middleAngleDelta = (180 - _sectorRotation - _sectorAngle) / 2;
            return GetUnitOnCircle(angle + middleAngleDelta);
        }



        private Vector3 GetUnitOnCircle(float angleDegrees)
        {
            var angleRadius = angleDegrees * Mathf.PI / 180f;

            var x = Mathf.Cos(angleRadius);
            var y = Mathf.Sin(angleRadius);

            return new Vector3(x, y, 0);

        }

        private void OnDisable()
        {
            TryStopRoutine();
        }

        private void OnDestroy()
        {
            TryStopRoutine();
        }

        private void TryStopRoutine()
        {
            if (_routine != null) StopCoroutine(_routine);
        }
    }
}