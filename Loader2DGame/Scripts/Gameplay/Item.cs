using UnityEngine;

[RequireComponent(typeof(Rigidbody2D))]
[RequireComponent(typeof(SpriteRenderer))]

public class Item : MonoBehaviour
{
    [SerializeField] private ItemResource _itemRes;

    private Rigidbody2D _rigidbody;
    private SpriteRenderer _spriteRenderer;

#if UNITY_EDITOR
    private void OnValidate()
    {
        GetComponent<SpriteRenderer>().sprite = _itemRes.ItemSprite;
        GetComponent<SpriteRenderer>().sortingLayerName = _itemRes.SortingLayerName;
    }
#endif

    private void Awake()
    {
        gameObject.tag = _itemRes.TagName;
        gameObject.layer = LayerMask.NameToLayer(_itemRes.LayerMaskName);

        _rigidbody = GetComponent<Rigidbody2D>();
        _rigidbody.mass = _itemRes.ItemWeight;
        _rigidbody.collisionDetectionMode = CollisionDetectionMode2D.Continuous;
        _rigidbody.sharedMaterial = _itemRes.PhysicMaterial;

        _spriteRenderer = GetComponent<SpriteRenderer>();
        _spriteRenderer.sortingLayerName = _itemRes.SortingLayerName;
    }
    private void OnBecameInvisible()
    {
        Destroy(gameObject);
    }
    private void OnDestroy()
    {
        Debug.Log($"Item {gameObject.name} was destroyed");
    }
}
