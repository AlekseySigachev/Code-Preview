using System;
using UnityEngine;
using UnityEngine.Events;

public class CarVolume : MonoBehaviour
{
    public UnityEvent<int> OnVolumeChange;

    private int _itemsInVolume;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.GetComponent<Item>())
            JoinToVolume();
    }

    private void JoinToVolume()
    {
        _itemsInVolume++;
        Debug.Log($"Item was added, now it's {_itemsInVolume}");
        OnVolumeChange?.Invoke(_itemsInVolume);
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.GetComponent<Item>())
            RemoveItemFromVolume();
    }
    private void RemoveItemFromVolume()
    {
        _itemsInVolume--;
        Debug.Log($"Item was removed, now it's {_itemsInVolume}");
        OnVolumeChange?.Invoke(_itemsInVolume);
    }
}
