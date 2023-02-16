using UnityEngine;

public class GoldHandler : MonoBehaviour
{
    private int _gold;
    public int Gold => _gold;

    public void AddGold(int gold)
    {
        _gold += gold;
    }

    public void SpendGold(int gold)
    {
        if(_gold > 0)
            _gold -= gold;
    }
}
