using MainNameSpace.Model;
using MainNameSpace.Model.Definitions;
using MainNameSpace.UI.Widgets;
using UnityEngine;
namespace MainNameSpace.UI.HUD
{
    public class HUDController : MonoBehaviour
    {
        [SerializeField] private ProgressBarWidget _healthBar;
        private GameSession _session;
        private void Start()
        {
            _session = FindObjectOfType<GameSession>();
            _session.data.Health.OnChanged += OnHelthChanged;
            OnHelthChanged(_session.data.Health.Value, 0);
        }
        private void OnHelthChanged(int newValue, int oldValue)
        {
            var maxHealth = DefsFacade.I.Player.MaxHealth;
            var value = (float)newValue / maxHealth;
            _healthBar.SetProgress(value);
        }
        private void OnDestroy()
        {
            _session.data.Health.OnChanged -= OnHelthChanged;
        }
    }
}