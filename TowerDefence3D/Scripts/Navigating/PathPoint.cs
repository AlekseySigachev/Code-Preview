using UnityEngine;

public class PathPoint : MonoBehaviour
{
    void Start()
    {
        if(GetComponent<MeshRenderer>())
            GetComponent<MeshRenderer>().enabled = false;
    }
}
