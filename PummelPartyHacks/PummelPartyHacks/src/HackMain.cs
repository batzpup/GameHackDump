using PummelPartyHacks.src.MinigameHelpers;
using PummelPartyHacks.src.Utilities;
using PummelPartyHacks.UI;
using PummelPartyHacks.Utilities;
using Rewired;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.Windows;

namespace PummelPartyHacks
{
    [SuppressMessage("ReSharper", "Unity.RedundantEventFunction")]
    public partial class HackMain : MonoBehaviour
    {

        public GuiHandler _guiHandler;
        MinigameController _minigameController;
        MinigameDefinition _currentMinigame;
        MinigameDefinition previousMinigame;
        MinigameDefinition nextMinigame;
        FieldInfo gameManagerFieldInfo;
        Helpers helpers;
        GameBoardState previousGameBoardState;
        public bool b_HandleCurrentMinigame;
        public bool b_SuperCheats = false;
        public bool b_ShowCheats = true;

        MortarMayhemHelper _mayhemHelper;
        MysteryMazeHelper _mysteryMazeHelper;
        SharkySwimHelper _sharkySwimHelper;
        SearingSpotlightHelper _searingSpotlightHelper;
        TreasureHunterHelper _sandySearchHelper;
        SwiftShootersHelper _swiftShootersHelper;
        BulletBarrageHelper _bulletBarrageHelper;

        public static Action onMiniGameChanged;


        /* - Initializing Methods - */
        public void Awake()
        {
            // This function is called when the class is loaded by the game (prior to attachment)
        }

        public void OnEnable()
        {
            // This function is called when the script is enabled by the parent object
        }

        public void Start()
        {
            // This function is called once for each instance of _localMortarMayhemPlayer class,
            // when it starts execution (in _localMortarMayhemPlayer case, attached to an object)
            ConsoleBase.WriteLine("HackMain Start()");
            m_Log.Log("Start()");
            m_Log.Error("Example Error");
            m_Log.Info("Information!");
            _mCamera = Camera.main;
            EntityUpdate = EntityUpdateFunct(0);
            StartCoroutine(EntityUpdate);
            helpers = gameObject.AddComponent<Helpers>();
            _guiHandler = gameObject.AddComponent<GuiHandler>();
            _guiHandler.Init(this);
            _minigameController = GameManager.Minigame;
            //GameManager.DEBUGGING = true;
            InitHelpers();
        }

        private void InitHelpers()
        {
            _mayhemHelper = new MortarMayhemHelper();
            _mayhemHelper.Init(this);
            _mysteryMazeHelper = new MysteryMazeHelper();
            _mysteryMazeHelper.Init(this);
            _sharkySwimHelper = gameObject.AddComponent<SharkySwimHelper>();
            _sharkySwimHelper.Init(this);
            _searingSpotlightHelper = gameObject.AddComponent<SearingSpotlightHelper>();
            _searingSpotlightHelper.Init(this);
            _sandySearchHelper = gameObject.AddComponent<TreasureHunterHelper>();
            _sandySearchHelper.Init(this);
            _swiftShootersHelper = gameObject.AddComponent<SwiftShootersHelper>();
            _swiftShootersHelper.Init(this);
            _bulletBarrageHelper = gameObject.AddComponent<BulletBarrageHelper>();
            _bulletBarrageHelper.Init(this);



        }
        public void ToggleShowCheats()
        {
            b_ShowCheats = !b_ShowCheats;
        }


        public void UnlockCloaks()
        {
            
            for (int i = 0; i < GameManager.unlocked.Length; i++)
            {
                GameManager.unlocked[i] = true;
            }
            GameManager.SaveUnlocks();
            UnlockWindowManager unlockWindow = FindObjectOfType<UnlockWindowManager>();
            if(unlockWindow != null)
            {
                Helpers.GetPrivateNonStaticMethod(unlockWindow, "UpdateUI").Invoke(unlockWindow, null);
            }
            
        }
        /* - Game Loop Methods - */
        public void Update()
        {

            if (UnityEngine.Input.GetKeyDown(KeyCode.Home))
            {
                ToggleShowCheats();
            }
            if (previousGameBoardState != GameManager.Board.BoardState)
            {
                ConsoleBase.WriteLine($"BoardState  Changed to: {GameManager.Board.BoardState}");
                if (previousGameBoardState == GameBoardState.Minigame)
                {
                    MinigameChanged();
                }
                previousGameBoardState = GameManager.Board.BoardState;
            }
            if (previousMinigame != _currentMinigame)
            {
                ConsoleBase.WriteLine($"Minigame Changed to: {GameManager.CurrentMinigameDef.minigameName}");
                previousMinigame = _currentMinigame;
                MinigameChanged();
            }
            if (GameManager.Board.BoardState == GameBoardState.Minigame)
            {
                _currentMinigame = GameManager.CurrentMinigameDef;
                if (b_HandleCurrentMinigame || b_SuperCheats)
                {
                    if (_minigameController == null)
                    {
                        _minigameController = FindObjectOfType<MinigameController>();
                    }
                    if (_currentMinigame == null)
                        return;
                    switch (_currentMinigame.minigameName)
                    {
                        case "Mortar Mayhem":
                            _mayhemHelper.HandleMortarMayhem();
                            break;
                        case "Mystery Maze":
                            _mysteryMazeHelper.HandleMysteryMaze();
                            break;
                        case "SharkySwim":
                            _sharkySwimHelper.HandleSharkySwim();
                            break;
                        case "Searing Spotlights":
                            _searingSpotlightHelper.HandleSearingSpotLight();
                            break;
                        case "Sandy Search":
                            _sandySearchHelper.HandleTreasureHunter();
                            break;
                        case "Swift Shooters":
                            _swiftShootersHelper.HandleSwiftShooters();
                            break;
                        case "Bullet Barrage":
                            _bulletBarrageHelper.HandleBulletBarrage();
                            break;
                        default:
                            break;
                    }
                    
                }
            }

        }
      

        private void MinigameChanged()
        {
            
        
            onMiniGameChanged.Invoke();
        }



        public void LateUpdate()
        {   // This function is called once per frame, it's frequency depends on the frame rate.
            // This is at the end of the game logic cycle.
        }
        public void OnGUI()
        {   // This function is called at the end of the frame, after all game logic.
            // It is called twice per frame: Once for rendering, and once for GUI Events
                if (b_HandleCurrentMinigame || b_SuperCheats)
                {
                    switch (_currentMinigame.minigameName)
                    {
                    case "Sandy Search":
                        _sandySearchHelper.OnGUI();
                        break;

                    default:
                        break;
                }

                }
        }

        /* - Physics Method - */
        public void FixedUpdate()
        {   // This function is called at a fixed frequency (Typically 100hz) and is independent of the frame rate.
            // For physics operations.
        }

        /* - Closing Methods - */
        public void OnDisable()
        {   // This function is called when the instance of the class is disabled by it's parent.
            // The component remains attached, but disabled (Component.ENABLED = false)
        }
        public void OnDestroy()
        {   // This function is called when the instance of the class is destroyed by it's parent.
            // The component and all it's data are destroyed and must be created again.
        }

        // Logic 
        public List<BoardPlayer> players;
        bool b_timeScaledChanged = false;
        public BoardPlayer localPlayer;


        public void MyHitDice(int amount)
        {
            GetAllPlayers();
            if (localPlayer.IsRollingDice == true && GameManager.Board.CurPlayer == localPlayer || GameManager.Board.BoardState == GameBoardState.DetermineTurnOrder)
            {
                if (amount >= 255)
                {
                    amount = 255;
                }

                GameManager.Board.QueueAction(new ActionHitDice(localPlayer.GamePlayer.GlobalID, (byte)amount), true, true);
                localPlayer.IsRollingDice = false;
            }
                
           
        }
   

        private void GetAllPlayers()
        {
            if (players == null)
            {
                players = FindObjectsOfType<BoardPlayer>().ToList();
            }
            if (localPlayer == null)
            {
                foreach (var player in players)
                {
                    if (player.GamePlayer.IsLocalPlayer && !player.GamePlayer.IsAI)
                    {
                        localPlayer = player;
                    }
                }
            }
        }

        public void GainItem(byte id)
        {
            GetAllPlayers();
            ConsoleBase.WriteLine($"Giving Item {GameManager.ItemList.items[(int)id].itemName}");
            localPlayer.GiveItem(id, true);

        }

        public void KillPlayer(string name)
        {
            if(players == null)
            {
                players = FindObjectsOfType<BoardPlayer>().ToList();
            }
            ConsoleBase.WriteLine($"Attempting to Kill {name}");
            foreach (var player in players)
            {
                if (player.GamePlayer.Name.ToLower() == name.ToLower())
                {
                    ConsoleBase.WriteLine($"Player {name} found: attempting to kill");
                    player.KillPlayer(player, player.transform.position, 30f);
                }
            }
        }

        public void AddGold(int amount)
        {
            GetAllPlayers();
            localPlayer.GiveGold(amount, true);
        }
        public void MultiplyGameSpeed(float speed)
        {
            b_timeScaledChanged = !b_timeScaledChanged;
            if (b_timeScaledChanged)
            {
                Time.timeScale = speed;
            }
            else
            {
                Time.timeScale = 1;
            }

        }

        public void RaiseMaxPlayers()
        {
            GameManager.LobbyMaxPlayers = 15;
        }
        public void ToggleCheatMinigames()
        {
            b_HandleCurrentMinigame = !b_HandleCurrentMinigame;
        }
        public void ToggleAutoPlay()
        {
            b_SuperCheats = !b_SuperCheats;
        }
        public void StartTurn()
        {
            GetAllPlayers();
            ConsoleBase.WriteLine($"Starting local players turn");
            localPlayer.StartTurn();
        }
        public void EndCurrentPlayersTurn()
        {
            GetAllPlayers();
            ConsoleBase.WriteLine($"Ending {GameManager.Board.CurPlayer.GamePlayer.Name}'s turn");
            if(GameManager.Board != null)
            {
                GameManager.Board.EndTurn();
            }
            else
            {
                ConsoleBase.WriteLine($"Gameboard is null");
            }
            
        }

        public void ShowAllMinigames()
        {
            
            foreach (var minigame in GameManager.GetMinigameList())
            {
                ConsoleBase.WriteLine($"Minigame: {minigame.minigameName}, Id: {minigame.minigameID}, Minigame def {minigame}");
            }
            ConsoleBase.WriteLine($"Total Minigames: {GameManager.GetMinigameList().Count}");
        }

    
            
        public void SetNextMinigame(string name)
        {
           var minigame = GameManager.GetMinigameByName(name);
            if( minigame != null)
            {
                GameManager.AddMinigame(minigame);
                ConsoleBase.WriteLine($"Next minigame is {minigame.minigameName}");
            }
            else
            {
                ConsoleBase.WriteLine($"That Minigame doesnt exist");
            }
        }
        public void StartMinigame()
        {
            MethodInfo dynMethod = GameManager.Board.GetType().GetMethod("StartMinigame", BindingFlags.NonPublic | BindingFlags.Instance);
            ConsoleBase.WriteLine($"Attempting to Invoke {dynMethod.Name}");
             var result = dynMethod.Invoke(GameManager.Board, null);
            ConsoleBase.WriteLine($"{dynMethod.Name} Invoked");
            if (GameManager.Board.CurnTurnNum > 0)
            {
                GameManager.Board.GetType().GetField("curTurnNum", BindingFlags.NonPublic | BindingFlags.Instance).SetValue(GameManager.Board, GameManager.Board.CurnTurnNum - 1);
            }
            

        }



     

    }
}