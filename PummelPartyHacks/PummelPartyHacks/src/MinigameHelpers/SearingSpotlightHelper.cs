using PummelPartyHacks.src.Utilities;
using PummelPartyHacks.Utilities;
using Rewired;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class SearingSpotlightHelper : MinigameHelper
    {

        List<SpeedySpotlightsPlayer> players;
        SpeedySpotlightsPlayer localPlayer;
        SpeedySpotlightsController controller;

        public void OnEnable()
        {
            HackMain.onMiniGameChanged += HandleOnMinigameChanged;
        }

        private void HandleOnMinigameChanged()
        {
            ConsoleBase.WriteLine($"Initialising Minigame");
            players.Clear();
            controller = null;
            localPlayer = null;
        }

        public void OnDisable()
        {
            HackMain.onMiniGameChanged -= HandleOnMinigameChanged;
        }

        public void HandleSearingSpotLight()
        {
            RenderSettings.ambientLight = Color.white;
            GetPlayers();
            GetController();
            if (controller != null)
            {
                Helpers.GetPrivateNonStaticField(controller, "pulseLength").SetValue(controller,1000f);
                ActionTimer pulseTimer = (ActionTimer) Helpers.GetPrivateNonStaticField(controller, "pulseTimer").GetValue(controller);
                
                pulseTimer.SetInterval(45f);
                Helpers.GetPrivateNonStaticField(controller, "pulseTimer").SetValue(controller,pulseTimer);
                controller.pulsing = true;
            }
           
            
        }


        void GetController()
        {
            if (controller == null)
            {
                controller = FindObjectOfType<SpeedySpotlightsController>();
            }
        }
        public void GetPlayers()
        {
            if (players == null)
            {
                ConsoleBase.WriteLine($"Getting Players");
                players = FindObjectsOfType<SpeedySpotlightsPlayer>().ToList();
                foreach (var player in players)
                {
                    if (player.GamePlayer.IsLocalPlayer && !player.GamePlayer.IsAI)
                    {
                        localPlayer = player;
                        return;
                    }
                }
            }
         
        }
    }
 }
