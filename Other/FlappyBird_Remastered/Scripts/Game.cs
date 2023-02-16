using UnityEngine;

public class Game : MonoBehaviour
{
    [SerializeField] private Bird _bird;
    [SerializeField] private PipeGenerator _pipeGenerator;
    [SerializeField] private StartScreen _startScreen;
    [SerializeField] private GameoverScreen _gameoverScreen;
    private void OnEnable()
    {
        _startScreen.onPlayButtonClicked += OnPlayButtonClicked;
        _gameoverScreen.onRestartButtonClicked += OnRestartButtonClicked;
        _bird.onGameOver += OnGameOver;

    }
    private void OnDisable()
    {
        _startScreen.onPlayButtonClicked -= OnPlayButtonClicked;
        _gameoverScreen.onRestartButtonClicked -= OnRestartButtonClicked;
        _bird.onGameOver -= OnGameOver;
    }
    private void Start()
    {
        Time.timeScale = 0;
        _startScreen.Open();
    }
    private void OnPlayButtonClicked()
    {
        _startScreen.Close();
        StartGame();
    }
    private void OnRestartButtonClicked()
    {
        _gameoverScreen.Close();
        _pipeGenerator.ResetPool();
        StartGame();
    }
    private void StartGame()
    {
        Time.timeScale = 1.0f;
        _bird.ResetPlayer();
    }
    public void OnGameOver()
    {
        Time.timeScale = 0;
        _gameoverScreen.Open();
    }
}