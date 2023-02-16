using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

[RequireComponent(typeof(BirdMove))]
public class Bird : MonoBehaviour
{
    private BirdMove _birdMove;
    private int _score;
    public event UnityAction onGameOver;

    private void Start()
    {
        _birdMove = GetComponent<BirdMove>();
    }

    public void ResetPlayer()
    {
        _score = 0;
        _birdMove.ResetBird();
    }
    public void Die()
    {
        onGameOver?.Invoke();
    }
    public void IncreaseScore()
    {
        _score++;
    }
}
