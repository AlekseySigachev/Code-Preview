using UnityEngine;

public class Porter : MonoBehaviour
{
    [SerializeField] private LayerMask _layers;
    [SerializeField] private Vector2 _cursorOffset;

    private Rigidbody2D _item = null;
    private Vector3 _offset;
    public bool IsDraggingItem => _item;

    private void Start()
    {
        //transform.eulerAngles = new Vector3(0f, 0f, 30f);
        //_spriteRenderer = GetComponent<SpriteRenderer>();
        //Cursor.visible = false;
        //instance = this;
    }
    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            RaycastHit2D hit = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), _cursorOffset, 1, _layers);
            if (hit)
            {
                _item = hit.rigidbody;
                _offset = _item.transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition);
            }
        }
        else if (Input.GetMouseButtonUp(0))
        {
            _item = null;
        }
        if (_item)
        {
            _item.MovePosition(Camera.main.ScreenToWorldPoint(Input.mousePosition) + _offset);
            _item.velocity = Vector2.zero;
        }
    }
}
