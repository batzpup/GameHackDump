using PummelPartyHacks.Utilities;
using System.Collections.Generic;
using UnityEngine;

namespace PummelPartyHacks.UI
{
    public class GuiHandler : MonoBehaviour
    {
        private GuiWindow Window;
        HackMain _hackMain;


        private List<GameObject> someObjects;

        public void Init(HackMain hackMain)
        {
            _hackMain = hackMain;
        }
        public void Start()
        {
            Window = gameObject.AddComponent<GuiWindow>();
            Window.Init(_hackMain);
            Window.SetWindowTitle("Cheat menu");
            Window.SetParameters(20, 200);
            Window.AddButton("Print GameObjects", () => _hackMain.PrintAllGameObjects());
            Window.AddNumField("Gain Gold", (int amount) => _hackMain.AddGold(amount));
            Window.AddNumField("Roll Dice", (int amount) => _hackMain.MyHitDice(amount));
            Window.AddNumField("Gain Item", (int id) => _hackMain.GainItem((byte)id));
            Window.AddStringFieldButtonContainer("Set next minigame", (string name) => _hackMain.SetNextMinigame(name));
            Window.AddFloatField("Multiply Time Scale", (float GameSpeed) => _hackMain.MultiplyGameSpeed(GameSpeed));
            Window.AddToggle("Cheat current minigame",() => _hackMain.ToggleCheatMinigames());
            Window.AddToggle("Super Cheaty", () => _hackMain.ToggleAutoPlay());
            Window.AddButton("Show all Minigames", () => _hackMain.ShowAllMinigames());
            Window.AddButton("Unlock Cloaks",() => _hackMain.UnlockCloaks());
            
            Window.AddLabel("Experimental: can cause crashes or invalid game states");
            Window.AddButton("Start Minigame", () => _hackMain.StartMinigame());
            Window.AddStringFieldButtonContainer("Kill Player", (string name) => _hackMain.KillPlayer(name));
            Window.AddButton("End Current Players Turn", () => _hackMain.EndCurrentPlayersTurn());
            




        }

        public void OnGUI()
        {
            
        }
    }
}