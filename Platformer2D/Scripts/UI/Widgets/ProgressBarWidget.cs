using UnityEngine;
using UnityEngine.UI;

namespace MainNameSpace.UI.Widgets
{
    public class ProgressBarWidget : MonoBehaviour
    {
        [SerializeField] private Image _bar;
        public void SetProgress(float progress)
        {
            _bar.fillAmount = progress;
        }
    }
}