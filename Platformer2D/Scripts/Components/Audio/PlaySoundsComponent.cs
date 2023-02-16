using UnityEngine;
namespace MainNameSpace.components.Audio
{
    public class PlaySoundsComponent : MonoBehaviour
    {
        [SerializeField] private AudioData[] _sounds;
        private AudioSource _source;

        public void Play(string id)
        {
            foreach(var audioData in _sounds)
            {
                if (_source == null)
                    _source = GameObject.FindWithTag("SFXAudioSource").GetComponent<AudioSource>();
                if (audioData.Id != id) continue;

                _source.PlayOneShot(audioData.Clip);
                break;
            }
        }

        [System.Serializable]
        public class AudioData
        {
            [SerializeField] private string _id;
            [SerializeField] private AudioClip _clip;

            public string Id => _id;
            public AudioClip Clip => _clip;
        }
    }
}
