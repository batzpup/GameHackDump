using PummelPartyHacks.src.Utilities;
using PummelPartyHacks.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class SwiftShootersHelper : MinigameHelper
    {
        List<SwiftShootersPlayer> shooters;
        SwiftShootersPlayer localPlayer;
        SwiftShooterTarget currentTarget;
        SwiftShootersController controller;
        SwiftShooterTargetSpawner spawner;
        float lastShootTime = 0f;
        float shootCooldown = 0.25f;
        float timer = 0;
        
        public void HandleSwiftShooters()
        {
            if (!hackMain.b_SuperCheats)
            {
                GetAllPlayers();
                if (!controller.Playable)
                    return;
                spawner = (SwiftShooterTargetSpawner)Helpers.GetPrivateNonStaticField(localPlayer, "m_spawner").GetValue(localPlayer);

                for (int i = 0; i < 3; i++)
                {
                    SwiftShooterTarget target = spawner.GetTarget(i);

                    if (target.GetTargetType() != TargetType.None && target.GetTargetType() != TargetType.Bomb && target.IsTargetUp())
                    {
                        currentTarget = target;
                        localPlayer.TargetPos = (byte)currentTarget.TargetIndex;
                        break;
                    }
                }
            }
            else
            {
                SuperCheat();
            }
         
        }


        public void SuperCheat()
        {
            GetAllPlayers();
            if (!controller.Playable)
                return;



            spawner = (SwiftShooterTargetSpawner)Helpers.GetPrivateNonStaticField(localPlayer, "m_spawner").GetValue(localPlayer);

            for (int i = 0; i < 3; i++)
            {
                SwiftShooterTarget target = spawner.GetTarget(i);

                if (target.GetTargetType() != TargetType.None && target.GetTargetType()!= TargetType.Bomb && target.IsTargetUp())
                {
                    currentTarget = target;
                    localPlayer.TargetPos = (byte)currentTarget.TargetIndex;
                    break;
                }
            }

            if (currentTarget != null)
            {
                bool canShoot = Time.time - lastShootTime > shootCooldown;
                ConsoleBase.WriteLine("Can Shoot: " + canShoot);
               
                    MethodInfo Fire = Helpers.GetPrivateNonStaticMethod(localPlayer, "Fire");
                    
                if (currentTarget.IsTargetUp() && currentTarget.GetTargetType() != TargetType.Bomb)
                {
                    
                    if (Time.time - lastShootTime > shootCooldown)
                    {
                        if (timer < 0.15f)
                        {
                            timer += Time.deltaTime;
                            
                        }
                        else
                        {
                            timer = 0f;
                            Fire.Invoke(localPlayer, null);
                            lastShootTime = Time.time;
                        }
                            
                        
                      
                    }
                }
            }
        }

        void GetAllPlayers()
        {
            
            if (shooters == null)
            {
                shooters = FindObjectsOfType<SwiftShootersPlayer>().ToList();

            }
            if(localPlayer == null)
            {
                foreach (var shooter in shooters)
                {
                    if (shooter.GamePlayer.IsLocalPlayer && !shooter.GamePlayer.IsAI)
                    {
                       
                        localPlayer = shooter;
                        break;
                    }
                }
            }
            if (controller == null)
            {
                ConsoleBase.WriteLine("Getting controller");
                controller = (SwiftShootersController)(Helpers.GetPrivateNonStaticField(localPlayer, "m_minigameController").GetValue(localPlayer));
            }

        }

    
    }
}
