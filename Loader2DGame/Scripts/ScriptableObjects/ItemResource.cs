using UnityEngine;
[CreateAssetMenu(menuName = "New Item")]
public class ItemResource : ScriptableObject
{
    [SerializeField] private Sprite _itemSprite;
    [SerializeField] private float _itemWeight;
    [SerializeField] private string _tagName = "Item";
    [SerializeField] private string _sortingLayerName = "Items";
    [SerializeField] private string _layerMaskName = "Item";
    [SerializeField] private PhysicsMaterial2D _physicMaterial;

    public float ItemWeight => _itemWeight;
    public string SortingLayerName => _sortingLayerName;
    public string TagName => _tagName;
    public string LayerMaskName => _layerMaskName;
    public Sprite ItemSprite => _itemSprite;
    public PhysicsMaterial2D PhysicMaterial => _physicMaterial;
}
