using UnityEngine;
namespace DinkumHack
{
    public class Loader
    {
        private static GameObject _gameObject;


        public static void Init()
        {
            _gameObject = new GameObject();
            _gameObject.AddComponent<Hack>();
            GameObject.DontDestroyOnLoad(_gameObject);

        }


        public static void Unload()
        {
            _Unload();
        }
        private static void _Unload()
        {
            GameObject.Destroy(_gameObject);
        }

    }
}