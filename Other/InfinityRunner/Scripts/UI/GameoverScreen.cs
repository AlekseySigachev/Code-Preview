using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

[RequireComponent(typeof(CanvasGroup))]
public class GameoverScreen : MonoBehaviour
{
    [SerializeField] private Button _restartButton;
    [SerializeField] private Button _exitButton;
    [SerializeField] private Player _player;

    private CanvasGroup _gameoverGroup;

    private void Start()
    {
        _gameoverGroup = GetComponent<CanvasGroup>();
        _gameoverGroup.alpha = 0;
        _restartButton.onClick.AddListener(OnRestartButtonClick);
        _exitButton.onClick.AddListener(OnExitButtonClick);
    }
    private void OnEnable()
    {
        _player.OnPlayerDied += _player_OnPlayerDied;
        _restartButton.onClick.RemoveListener(OnRestartButtonClick);
        _exitButton.onClick.RemoveListener(OnExitButtonClick);
    }

    private void _player_OnPlayerDied()
    {
        _gameoverGroup.alpha = 1;
        Time.timeScale = 0;
    }

    private void OnDisable()
    {
        _player.OnPlayerDied -= _player_OnPlayerDied;
    }

    private void OnRestartButtonClick()
    {
        Time.timeScale = 1;
        ReloadLevel();
    }
    private void OnExitButtonClick()
    {
        Application.Quit();
    }
    private void ReloadLevel()
    {
        int _currentSceneIndex = SceneManager.GetActiveScene().buildIndex;
        SceneManager.LoadScene(_currentSceneIndex);
    }
}
