using UnityEngine;

[RequireComponent(typeof(Unit))]
public class WaypointMovement : MonoBehaviour
{
    private Transform _path;

    private Transform[] _points;
    private Unit _unit;

    private int _currentPointIndex;
    private void Start()
    {
        _path = FindObjectOfType<Path>().transform;
        _unit = GetComponent<Unit>();
        _points = new Transform[_path.childCount];

        for (int i = 0; i < _path.childCount; i++)
        {
            _points[i] = _path.GetChild(i);
        }
    }
    private void Update()
    {
        Transform target = _points[_currentPointIndex];
        var direction = (target.position - transform.position).normalized;

        transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.LookRotation(direction), Time.deltaTime * 10.0f);
        transform.position = Vector3.MoveTowards(transform.position, target.position, _unit.MovementSpeed * Time.deltaTime);

        if (transform.position.x == target.position.x)
        {
            _currentPointIndex++;
            if (_currentPointIndex >= _points.Length)
            {
                _currentPointIndex = 0;
            }
        }
    }
}
