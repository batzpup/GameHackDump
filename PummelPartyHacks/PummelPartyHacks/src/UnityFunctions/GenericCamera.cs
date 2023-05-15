using PummelPartyHacks.src.Utilities;
using UnityEngine;

namespace PummelPartyHacks
{
    partial class HackMain : MonoBehaviour
    {
        // Setup a local camera
        public Camera _mCamera;
        private void AssignCamera()
        { // Set out camera to reference the main (Current) camera in the host game
            _mCamera = Camera.main;
        }

        private Vector3 W2S(Vector3 worldPosition, Camera camera)
        { // Returns the screen position of a point in 3D space (relative to the camera)
            return camera.WorldToScreenPoint(worldPosition);
        }

        private float Distance(Vector3 worldPosition, Camera camera)
        { // Returns the distance from the camera to a point in 3D space
            return Vector3.Distance(camera.transform.position, worldPosition);
        }

        public void Basic_ESP(Transform transform, Camera camera, Texture2D texture)
        { // Simple ESP function that uses an object transform and retrieves the position in 3D space
            Vector3 pos = camera.WorldToScreenPoint(transform.position);
            if (pos.z > 0f)
            {
                float distance = Vector3.Distance(_mCamera.transform.position, transform.position);
                Helpers.Box(pos.x, Screen.height - pos.y, 50 / 1.8f, 50, texture, 1f);
            }
        }

        public void Basic_ESP(Vector3 worldPosition, Camera camera,Texture2D texture)
        { // Simple ESP function that takes a point in 3D space as a parameter
            Vector3 pos = camera.WorldToScreenPoint(worldPosition);
            if (pos.z > 0f)
            {
               // float distance = Vector3.Distance(_mCamera.transform.position, transform.position);
                Helpers.Box(pos.x, Screen.height - pos.y, 50 / 1.8f, 50, texture, 1f);
            }
        }

        public void Basic_ESP(Vector3 worldPosition, string text, Camera camera)
        { // Simple ESP function that takes a point in 3D space as a parameter
            Vector3 pos = camera.WorldToScreenPoint(worldPosition);
            if (pos.z > 1f)
            {
                int numLines = text.Split('\n').Length;
                float distance = Vector3.Distance(_mCamera.transform.position, worldPosition);
                GUI.Label(new Rect(
                            pos.x,
                            Screen.height - pos.y,
                            pos.x + (text.Length * GUI.skin.label.fontSize),
                            Screen.height - pos.y + GUI.skin.label.fontSize * 2),
                            text);
            }
        }

    }
}