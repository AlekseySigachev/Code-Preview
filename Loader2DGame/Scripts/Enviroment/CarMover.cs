using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarMover : MonoBehaviour
{
    [SerializeField][Range(0, 10)] private float _speed;
    [SerializeField][Range(0, 100)] private float _wheelsSpeed;

    [SerializeField] List<Transform> Wheels;

    private Item[] _items;

    private void Start()
    {
        _items = FindObjectsOfType<Item>();
    }
    public void PlayerWin()
    {
        Debug.Log("Cat moving");
        StartCoroutine(StartMovingCar());
    }
    private void MoveCar()
    {
        float newPosX = transform.position.x + -_speed * Time.deltaTime;
        transform.position = new Vector3(newPosX, transform.position.y, transform.position.z);
        foreach (var item in Wheels)
        {
            item.eulerAngles = new Vector3(0, 0, item.eulerAngles.z + _wheelsSpeed * Time.deltaTime);
        }
    }
    private void MoveItems()
    {
        foreach (Item item in _items)
        {
            if (item != null)
            {
                float newPosX = item.transform.position.x + -_speed * Time.deltaTime;
                item.transform.position = new Vector3(newPosX, item.transform.position.y, transform.position.z);
            }
        }
    }
    private void OnBecameInvisible()
    {
        Destroy(gameObject);
    }
    private IEnumerator StartMovingCar()
    {
        while (true)
        {
            MoveCar();
            MoveItems();

            yield return new WaitForFixedUpdate();
        }
    }
}
