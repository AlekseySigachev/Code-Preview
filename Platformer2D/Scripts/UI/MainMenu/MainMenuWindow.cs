using System;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace MainNameSpace.UI.MainMenu
{
    public class MainMenuWindow : AnimatedWindow
    {
        private Action _closeAction;
        public void OnShowSettings()
        {
            var window = Resources.Load<GameObject>("UI/SettingsWindow");
            var canvas = FindObjectOfType<Canvas>();
            Instantiate(window, canvas.transform);
        }
        public void OnGameStart()
        {
            _closeAction = () =>
            {
                SceneManager.LoadScene("StartLevel");
            };
            Close();
        }
        public void OnExit()
        {
            _closeAction = () =>
            {
                Application.Quit();
#if UNITY_EDITOR
                UnityEditor.EditorApplication.isPlaying = false;
#endif
            };
            Close();
        }
        public override void OnCloseAnimationComplite()
        {
            base.OnCloseAnimationComplite();
            _closeAction?.Invoke();
        }
    }
}