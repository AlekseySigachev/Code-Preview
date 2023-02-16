using UnityEngine;
using MainNameSpace.Model.Data;
using UnityEngine.SceneManagement;

namespace MainNameSpace.Model
{
    public class GameSession : MonoBehaviour
    {
        [SerializeField] private PlayerData _data;
        public PlayerData data => _data;
        private PlayerData _save;
        public QuickInventoryModel QuickInventory { get; private set; }

        private void Awake()
        {
            LoadHUD();
            if (IsSessionExit())
            {
                Destroy(gameObject);
            }
            else
            {
                InitModels();
                Save();
                DontDestroyOnLoad(this);
            }
        }

        private void InitModels()
        {
            QuickInventory = new QuickInventoryModel(data);
        }

        private void LoadHUD()
        {
            SceneManager.LoadScene("HUD", LoadSceneMode.Additive);
        }

        public void Save()
        {
            _save = data.Clone();
        }
        public void LoadLastSave()
        {
            _data = _save.Clone();
        }

        private bool IsSessionExit()
        {
            var sessions = FindObjectsOfType<GameSession>();
            foreach (var gameSession in sessions)
            {
                if (gameSession != this)
                    return true;
            }
            return false;
        }
    }
}

