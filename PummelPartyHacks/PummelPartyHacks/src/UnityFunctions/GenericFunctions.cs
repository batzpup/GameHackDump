using PummelPartyHacks.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace PummelPartyHacks
{
    public partial class HackMain : MonoBehaviour
    {

        public void GetAllGameObjects(out List<GameObject> gameObjects)
        {
            ConsoleBase.WriteLine("getting all GameObjects");
            Scene scene = SceneManager.GetActiveScene();
            gameObjects = new List<GameObject>(scene.rootCount + 1);
            scene.GetRootGameObjects(gameObjects);

            
        }
        public void PrintAllGameObjects()
        {

            ConsoleBase.WriteLine("Printing all GameObjects");
            
            List<GameObject> gameObjects;
            GetAllGameObjects(out gameObjects);
            foreach (var rootObject in gameObjects)
            {
                ConsoleBase.WriteLine($"Root Objects: {rootObject.name}");
                GetAllComponents(rootObject);
                for (int i = 0; i < rootObject.transform.childCount; i++)
                {
                    ConsoleBase.WriteLine($"Child of {rootObject.name}: {rootObject.transform.GetChild(i).gameObject.name}");
                    GetAllComponents(rootObject.transform.GetChild(i).gameObject);
                }
            }
        }
        public void GetAllComponents(GameObject gameObject)
        {
            var allComponents = new List<Component>();
            allComponents =  gameObject.GetComponents<Component>().ToList();
            foreach (var component in allComponents)
            {
                ConsoleBase.WriteLine($"Component: {component.name}");
            }
           
        }
       
        private bool Vector3InRange(Vector3 point1, Vector3 point2, float tolerance)
        { // Compares two 3D points relative to each other within a tolerance
            return Vector3.Distance(point1, point2) <= tolerance;
        }

        private bool IsVisible(GameObject target, Vector3 origin, LayerMask mask)
        { // Casts a ray to an object and returns true if the target object is hit
            Ray ray = new Ray(origin, (target.transform.position - origin).normalized);
            if (Physics.Raycast(ray, out RaycastHit hit, Single.PositiveInfinity, mask))
            {
                if (hit.collider.gameObject == target)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            return true;
        }

        private GameObject RayCastToPoint(Vector3 pos, Vector3 origin, LayerMask mask)
        { // Casts a ray between two points and returns the first GameObject between them, from the origin side.
            Ray ray = new Ray(origin, (pos - origin).normalized);

            if (Physics.Raycast(ray, out RaycastHit hit, Single.PositiveInfinity, mask))
            {
                return hit.collider.gameObject;
            }
            return new GameObject("No Object");
        }

      
    }
}