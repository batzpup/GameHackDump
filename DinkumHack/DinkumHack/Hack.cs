using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace DinkumHack
{
    class Hack: MonoBehaviour
    {
        CharLevelManager characterLevelManager;
        CharMovement charMovement;
        BankMenu bank;
        PermitPointsManager permitPointsManager;
        WorldManager worldManager;
        StatusManager statusManager;
        HuntingChallengeManager huntingChallengeManager;
        DeedManager deedManager;
        LicenceManager licenceManager;


        bool espEnabled = false;            
        int hackSpeed = 35 ;
        float verticalFlySpeed = 6;
        bool speedHacking = false;
        List<AnimalAI> animals = new List<AnimalAI>();
        bool GravityEnabled = true;
        Camera camera;

        public void Start()
        {
            characterLevelManager = FindObjectOfType<CharLevelManager>();
            charMovement = FindObjectOfType<CharMovement>();
            bank = FindObjectOfType<BankMenu>();
            permitPointsManager = FindObjectOfType<PermitPointsManager>();
            worldManager = FindObjectOfType<WorldManager>();
            statusManager = FindObjectOfType<StatusManager>();
            huntingChallengeManager = FindObjectOfType<HuntingChallengeManager>();
            deedManager = FindObjectOfType<DeedManager>();
            licenceManager = FindObjectOfType<LicenceManager>();
            camera = Camera.main;
        }

        public void Update()
        {
            if (camera == null)
                camera = Camera.main;
            
            statusManager.changeStamina(statusManager.getStaminaMax());
            statusManager.changeHealthTo(100);
            if (Input.GetKeyDown(KeyCode.K))
            {
                CallOfTheWild();
            }
            if (Input.GetKeyDown(KeyCode.L))
            {
                AddMoney(100000);
            }
            if (Input.GetKeyDown(KeyCode.P))
            {
                AddPermitPoints(1000);

            }
            if (Input.GetKeyDown(KeyCode.Y))
            {
                ToggleSpeedHack();

            }
            if (Input.GetKeyDown(KeyCode.F7))
            {
                LevelUpAllSkills();
            }
            if (Input.GetKeyDown(KeyCode.F6))
            {
                PayTownDebt();
            }
            if (Input.GetKeyDown(KeyCode.F4))
            {
                UnlockAllDeeds();
            }
            if (Input.GetKeyDown(KeyCode.F))
            {
                ToggleFlyHack();

            }
            if (Input.GetKeyDown(KeyCode.End))
            {

                espEnabled =!espEnabled;
                

            }
            if (Input.GetKeyDown(KeyCode.Home))
            {
                TeleportToSpawn();

            }
            if (Input.GetKeyDown(KeyCode.Pause))
            {
                UnlockAllLicenses();
            }


            FlyHackLogic();
            SpeedHackLogic();
        }

        private void SpeedHackLogic()
        {
            if (charMovement == null)
            {
                charMovement = FindObjectOfType<CharMovement>();
            }
            else
            {
                if (speedHacking)
                {
                    charMovement.setSpeedDif(hackSpeed);
                }
                else
                {
                    charMovement.setSpeedDif(1);
                }

            }
        }

        private void FlyHackLogic()
        {
            Rigidbody rigidbody = charMovement.GetComponent<Rigidbody>();
            if (!GravityEnabled)
            {
                charMovement.fallSpeed = 0;

                rigidbody.useGravity = false;
                charMovement.grounded = true;
                if (Input.GetKey(KeyCode.DownArrow))
                {
                    charMovement.transform.position =
                        new Vector3(charMovement.transform.position.x,
                        charMovement.transform.position.y - verticalFlySpeed * Time.deltaTime,
                        charMovement.transform.position.z);
                }
                if (Input.GetKey(KeyCode.UpArrow))
                {
                    charMovement.transform.position =
                        new Vector3(charMovement.transform.position.x,
                        charMovement.transform.position.y + verticalFlySpeed * Time.deltaTime,
                        charMovement.transform.position.z);
                }
            }
            else
            {
                charMovement.fallSpeed = 1;
                rigidbody.useGravity = true;
                
            }
        }

        private void CallOfTheWild()
        {
            animals.Clear();
            animals = FindObjectsOfType<AnimalAI>().ToList();
            foreach (var animal in animals)
            {
                StartCoroutine(animal.callAnimalToPos(charMovement.transform.position));
            }
        }

        private static void AddMoney(int moneyToAdd)
        {
            if (Inventory.inv != null)
                Inventory.inv.changeWallet(moneyToAdd, true);
        }

        private void AddPermitPoints(int pointsToAdd)
        {
            if (permitPointsManager == null)
            {
                permitPointsManager = FindObjectOfType<PermitPointsManager>();
            }
            else
            {
                permitPointsManager.addPoints(pointsToAdd);
            }
        }

        private void ToggleSpeedHack()
        {
            
                speedHacking = !speedHacking;
            
        }

        private void LevelUpAllSkills()
        {
            if (characterLevelManager == null)
            {
                characterLevelManager = FindObjectOfType<CharLevelManager>();
            }
            else
            {
                foreach (CharLevelManager.SkillTypes skillType in Enum.GetValues(typeof(CharLevelManager.SkillTypes)))
                {
                    characterLevelManager.addXp(skillType, characterLevelManager.getLevelRequiredXP((int)skillType));
                }



            }
        }

        private void PayTownDebt()
        {
            if (charMovement == null)
            {
                charMovement = FindObjectOfType<CharMovement>();
            }
            else
            {
                charMovement.CmdPayTownDebt(1000000);
                if (NetworkMapSharer.share.townDebt == 0)
                {
                    ConversationManager.manage.talkToNPC(NPCManager.manage.sign, TownManager.manage.debtComplete, false, false);
                }
            }
        }

        private void UnlockAllDeeds()
        {
            if (deedManager == null)
            {
                deedManager = FindObjectOfType<DeedManager>();
            }
            else
            {
                foreach (var deed in deedManager.deedDetails)
                {
                    deed.unlocked = true;

                }
            }
        }

        private void ToggleFlyHack()
        {
            GravityEnabled = !GravityEnabled;
           
        }

        private void TeleportToSpawn()
        {
            if (charMovement != null && worldManager != null)
            {
                int[] pos = new int[3];
                pos[0] = 10; //(int)worldManager.spawnPos.position.x;
                pos[1] = 10;//(int)worldManager.spawnPos.position.y;
                pos[2] = 10; // (int)worldManager.spawnPos.position.z;
                StartCoroutine(charMovement.teleportCharToPos(pos));
            }
        }

        private void UnlockAllLicenses()
        {
            if (licenceManager != null)
            {
                foreach (var licence in licenceManager.allLicences)
                {
                    
                    licence.isUnlocked = true;
                    licence.hasBeenSeenBefore = true;
                    licence.currentLevel = licence.getMaxLevel();
                    LicenceManager.manage.checkForUnlocksOnLevelUp(licence, false);

                }
            }
        }

        public void OnGUI()
        {   // This function is called at the end of the frame, after all game logic.
            // It is called twice per frame: Once for rendering, and once for GUI Events
            // This is where we do all drawing operations
            if (espEnabled)
            {
                GUI.Label(new Rect(1000, 100, 300, 100), "Esp Enabled");

                foreach (var animal in animals)
                {
                    GUI.Label(new Rect(1000, 300, 300, 100), $"{animal.animalName} {animal.getHealth()}");
                    Basic_ESP(animal.transform, $"{animal.animalName} {animal.getHealth()}");
                }
            }
           

        }

        private Vector3 W2S(Vector3 worldPosition)
        { // Returns the screen position of a point in 3D space (relative to the camera)

            return camera.WorldToScreenPoint(worldPosition);

        }

        private void Basic_ESP(Transform transform, string text)
        { // Simple ESP function that uses an object transform and retrieves the position in 3D space
            Vector3 pos = camera.WorldToScreenPoint(transform.position);
            if (pos.z > 0)
            {
                float distance = Vector3.Distance(camera.transform.position, transform.position);
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
