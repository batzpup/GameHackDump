using System;
using System.Runtime.InteropServices;
using UnityEngine;



namespace MonsterTrainHacks

{
    class Hack : MonoBehaviour
    {

        private PlayerManager playerManager;
        CombatManager combatManager;
        RoomManager roomManager;
        CardManager cardManager;
        List<RoomState> rooms = new List<RoomState>();
        List<CharacterState> characters = new List<CharacterState> ();

      
        public void Start()
        {
           
            
            playerManager = FindObjectOfType<PlayerManager>();
            combatManager = FindObjectOfType<CombatManager>();
            roomManager = FindObjectOfType<RoomManager>();
            cardManager = FindObjectOfType<CardManager>();
            
          
            
        }
        public void Update()
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                playerManager.AddEnergy(100);
                
            }
            if (Input.GetKeyDown(KeyCode.G))
            {
                playerManager.AdjustGold(100);
                

            }
            if (Input.GetKeyDown(KeyCode.P))
            {
                if (cardManager != null)
                {
                    var cards = cardManager.GetAllCards();
                    foreach (var card in cards)
                    {
                        StartCoroutine(cardManager.PurgeCard(card));
                    }
                }
            }
            if(Input.GetKeyDown(KeyCode.K))
            {

                if (roomManager == null)
                {
                    roomManager = FindObjectOfType<RoomManager>();
                }
                if (roomManager == null)
                {
                    return;
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {

                        rooms.Add(roomManager.GetRoom(i));
                    }
                }

                characters.Clear();
                foreach (RoomState room in rooms)
                {
                    room.AddCharactersToList(characters,Team.Type.Heroes, false);
                    
                }
                foreach (CharacterState character in characters)
                {
                    StartCoroutine(character.Sacrifice(null, false, false));
                    

                }
                

            }
            
        }
        public void OnGUI()
        {
            


        }
    }
}
