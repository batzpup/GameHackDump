using PummelPartyHacks.src.Utilities;
using PummelPartyHacks.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class TreasureHunterHelper : MinigameHelper
    {
        List<TreasureHuntPlayer> players;
        List<TreasureHuntObject> gems;
        TreasureHuntTreasure treasure;
        TreasureHuntPlayer localPlayer;


        public void HandleTreasureHunter()
        {
            GetAll();
            hackMain._mCamera = Camera.main;
            if (hackMain.b_SuperCheats)
            {
                
                Helpers.GetPrivateNonStaticField(localPlayer, "lastDigTime").SetValue(localPlayer, 0f);
                Helpers.GetPrivateNonStaticField(localPlayer, "curDigInterval").SetValue(localPlayer, 0f);
                Helpers.GetPrivateNonStaticField(localPlayer, "maxDigDistance").SetValue(localPlayer, 50f);
            }
        }

        public void OnGUI()
        {
            if (hackMain != null)
            {
                
                foreach (var gem in gems)
                {
                    hackMain.Basic_ESP(gem.transform.position, localPlayer.cam, Helpers.greenTexture);
                }
                hackMain.Basic_ESP(treasure.transform.position, localPlayer.cam, Helpers.redTexture);
            }
        }

            public void GetAll()
        {
            if (players == null)
            {
                
                players = FindObjectsOfType<TreasureHuntPlayer>().ToList();
                if (players != null)
                {
                    ConsoleBase.WriteLine("Got Players");
                }
            }
            if (localPlayer == null)
            {
                foreach (var player in players)
                {
                    if(player.GamePlayer.IsLocalPlayer && !player.GamePlayer.IsAI)
                    {
                        localPlayer = player;
                        ConsoleBase.WriteLine("Got local Player");
                        break;
                    }
                }
            }
            if (treasure == null)
            {
                treasure = localPlayer.minigameController.treasure;
                if (treasure != null)
                {
                    ConsoleBase.WriteLine("Got Treasure");
                }
                
            }
            if (gems == null)
            {
                gems = FindObjectsOfType<TreasureHuntObject>().ToList();
                ConsoleBase.WriteLine($"Got Gems & Treasure {gems.Count}");
            }
            
            
        }
    }
}
