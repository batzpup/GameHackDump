using PummelPartyHacks.Utilities;
using System.Collections;
using System.Diagnostics.CodeAnalysis;
using System.Reflection;
using UnityEngine;

namespace PummelPartyHacks
{
    partial class HackMain : MonoBehaviour
    {
        private IEnumerator EntityUpdate;
        private IEnumerator EntityUpdateFunct(float time)
        {
            yield return new WaitForSeconds(time);
            // Update Entities here //

            AssignCamera();
            gameManagerFieldInfo = typeof(GameBoardController).GetField("nextMinigame", BindingFlags.NonPublic | BindingFlags.Instance);
            nextMinigame = (MinigameDefinition)gameManagerFieldInfo.GetValue(GameManager.Board);
            ConsoleBase.WriteLine($"Next Minigame {nextMinigame.minigameName}");
            //ConsoleBase.WriteLine($"Current state; {GameManager.Board.BoardState.ToString()}");
            //ConsoleBase.WriteLine("EntityUpdate executed");
            EntityUpdate = EntityUpdateFunct(5);
            StartCoroutine(EntityUpdate);
        }
    }
}