using UnityEngine;
using UnityEngine.SceneManagement;
using MainNameSpace.Model;
namespace MainNameSpace.components.LevelManagement
{
    public class ReloadLevelComponent : MonoBehaviour
    {
        
        public void Reload()
        {
            var session = FindObjectOfType<GameSession>();
            session.LoadLastSave();

            var scene = SceneManager.GetActiveScene();
            SceneManager.LoadScene(scene.name);
        }

    }
    

}
