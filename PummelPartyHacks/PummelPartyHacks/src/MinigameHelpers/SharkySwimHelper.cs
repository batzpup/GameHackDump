
using PummelPartyHacks.src.Utilities;
using PummelPartyHacks.Utilities;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection;
using UnityEngine;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class SharkySwimHelper : MinigameHelper
    {
        List<FinderPlayer> _players = new List<FinderPlayer>();
        FinderPlayerShark sharkPlayer;
        List<GameObject> cubes = new List<GameObject> ();
  

        List<FinderPlayer> GetPlayers()
        {

            sharkPlayer = FindObjectOfType<FinderPlayerShark>();
            return FindObjectsOfType<FinderPlayer>().ToList();
        }
        public void OnEnable()
        {
            HackMain.onMiniGameChanged += HandleOnMinigameChanged;
        }


        public void OnDisable()
        {
            HackMain.onMiniGameChanged -= HandleOnMinigameChanged;
        }

        private void HandleOnMinigameChanged()
        {
           
                ConsoleBase.WriteLine($"Initialising Minigame");
                _players.Clear();
                foreach (var cube in cubes)
                {
                    Destroy(cube);
                }
                cubes.Clear();
                sharkPlayer = null;
            
       
        }

        public void HandleSharkySwim()
        {
   

            if (_players.Count < 2)
            {
                _players = GetPlayers();
                ConsoleBase.WriteLine($"Players Found: {_players.Count} players");
                foreach (var player in _players)
                {
                   GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
                    cube.GetComponent<BoxCollider>().enabled = false;
                    cubes.Add(cube);
                }
            }
            if (sharkPlayer.GamePlayer.IsLocalPlayer && !sharkPlayer.GamePlayer.IsAI)
            {
                var targetID = (byte)sharkPlayer.GetType().GetField("targetID", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(sharkPlayer);
                if (sharkPlayer.GamePlayer.RewiredPlayer.GetButtonDown(InputActions.Action1) && targetID != 255)
                {
                    
                  sharkPlayer.StartCoroutine("SharkAttack",targetID);
                 // ConsoleBase.WriteLine($"Im attacking");
                }
            }
            for (int i = 0; i < _players.Count; i++)
            {
                if (!_players[i].IsDead || !_players[i].escaped)
                {
                    cubes[i].transform.position = _players[i].transform.position;
                }
                else
                {
                    
                    Destroy(cubes[i].gameObject);
                    cubes.RemoveAt(i);
                }
                
            }

        }
    }

        
 }

