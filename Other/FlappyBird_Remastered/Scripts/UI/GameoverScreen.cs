using UnityEngine;
using UnityEngine.Events;

public class GameoverScreen : Screen
{
    public event UnityAction onRestartButtonClicked;
    public override void Close()
    {
        CanvasGroup.alpha = 0;
        Button.interactable = false;
        gameObject.SetActive(false);
    }

    public override void Open()
    {
        CanvasGroup.alpha = 1;
        Button.interactable = true;
        gameObject.SetActive(true);
    }

    protected override void OnButtonClick()
    {
        onRestartButtonClicked?.Invoke();
    }
}
