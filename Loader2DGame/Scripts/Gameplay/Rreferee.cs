using System.Collections;
using System.Linq;
using UnityEngine;
using UnityEngine.Events;

public class Rreferee : MonoBehaviour
{
    [SerializeField] private int _winDelay;

    private Porter _porter;
    private Item[] _itemsOnLevel;
    private int _itemsOnLevelCount;
    private int _playerItems;
    private bool _isTryingToWin;

    private Coroutine _tryingToWinCoroutine;

    public UnityEvent OnPlayerWin;

    private void Start()
    {
        _itemsOnLevel = FindObjectsOfType<Item>();
        _itemsOnLevelCount = _itemsOnLevel.Length;

        _porter = FindObjectOfType<Porter>();
    }

    public void TryToWin(int items)
    {
        _playerItems = items;

        if (_playerItems == _itemsOnLevelCount && !_isTryingToWin)
        {
            _tryingToWinCoroutine = StartCoroutine(TryingToWin());
        }
        else if (_tryingToWinCoroutine != null)
        {
            StopCoroutine(_tryingToWinCoroutine);
            _isTryingToWin = false;
        }
    }

    private IEnumerator TryingToWin()
    {
        _isTryingToWin = true;
        var delay = new WaitForSeconds(_winDelay);
        while (true)
        {
            if (CheckWinConditional(_playerItems))
            {
                OnPlayerWin?.Invoke();
                _isTryingToWin = false;
                StopCoroutine(_tryingToWinCoroutine);
            }
            yield return delay;
        }
    }

    private bool CheckWinConditional(int value)
    {
        return _itemsOnLevelCount == value && IsItemsStopped() && !_porter.IsDraggingItem;
    }

    private bool IsItemsStopped()
    {
        var item = _itemsOnLevel.FirstOrDefault(item => item.GetComponent<Rigidbody2D>().angularVelocity == 0);
        Debug.Log(item);
        return item;
/*        foreach (var item in _itemsOnLevel)
        {
            if (item.GetComponent<Rigidbody2D>().velocity != Vector2.zero)
                return false;
        }
        return true;*/
    }
}
