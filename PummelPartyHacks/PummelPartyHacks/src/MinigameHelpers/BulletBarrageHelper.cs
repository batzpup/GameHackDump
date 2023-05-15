using PummelPartyHacks.src.Utilities;
using PummelPartyHacks.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using ZP.Utility;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class BulletBarrageHelper : MinigameHelper
    {
        List<BulletDodgePlayer> players;
        BulletDodgePlayer localPlayer;
        BulletDodgeController controller;


        public void HandleBulletBarrage()
        {
            GetAllPlayers();
            GetLocalPlayer();
            GetController();
            if (hackMain.b_SuperCheats)
            {
                SuperCheats();
            }
            else
            {
                NormalCheats();
            }
        }


        private void SuperCheats()
        {

            if (localPlayer == null)
                return;

            Helpers.GetPrivateNonStaticField(localPlayer, "cur_state").SetValue(localPlayer, BulletDodgePlayer.BulletDodgePlayerState.Immune);
            localPlayer.immunity_length = 1000f;

        }

        private void GetLocalPlayer()
        {
            if (localPlayer == null && players != null)
            {
                foreach (var player in players)
                {
                    if (player.GamePlayer.IsLocalPlayer && !player.GamePlayer.IsAI)
                    {
                        localPlayer = player;
                        ConsoleBase.WriteLine("Got Local Player");
                        break;
                    }
                }
            }
        }

        private void GetAllPlayers()
        {
            if (players == null)
            {
                players = FindObjectsOfType<BulletDodgePlayer>().ToList();
                ConsoleBase.WriteLine("Got All Players");
            }
        }
        void GetController()
        {
            if (controller == null)
            {
                controller = FindObjectOfType<BulletDodgeController>();
            }
        }

        private void NormalCheats()
        {

            localPlayer.curSpeed = Mathf.Lerp(localPlayer.curSpeed, localPlayer.tarSpeed, Time.deltaTime);
            using (List<BulletDodgeProjectile>.Enumerator enumerator = BulletDodgeProjectile.projectiles.GetEnumerator())
            {
                while (enumerator.MoveNext())
                {
                    BulletDodgeProjectile bulletDodgeProjectile = enumerator.Current;
                    if ((localPlayer.transform.position - bulletDodgeProjectile.transform.position).sqrMagnitude < 75f && ((bulletDodgeProjectile.velocity.x < -0.1f && bulletDodgeProjectile.transform.position.x > base.transform.position.x) || (bulletDodgeProjectile.velocity.x > 0.1f && bulletDodgeProjectile.transform.position.x < base.transform.position.x)))
                    {
                        switch (bulletDodgeProjectile.type)
                        {
                            case BulletDodgeBulletType.Unassigned:
                                Debug.Log("Bullet Type not Set");
                                break;
                            case BulletDodgeBulletType.Left3:
                                base.StartCoroutine(this.DodgeNormal(true, false));
                                break;
                            case BulletDodgeBulletType.Right3:
                                base.StartCoroutine(this.DodgeNormal(false, false));
                                break;
                            case BulletDodgeBulletType.Left6:
                                base.StartCoroutine(this.DodgeNormal(true, true));
                                break;
                            case BulletDodgeBulletType.Right6:
                                base.StartCoroutine(this.DodgeNormal(false, true));
                                break;
                            case BulletDodgeBulletType.Spinner:
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            Vector3 vector = Vector3.one * 1000f;
            float num = float.MaxValue;
            bool flag = false;
            foreach (BulletDodgeProjectile bulletDodgeProjectile2 in BulletDodgeProjectile.projectiles)
            {
                if (bulletDodgeProjectile2.type == BulletDodgeBulletType.Spinner)
                {
                    flag = true;
                    float sqrMagnitude = (bulletDodgeProjectile2.spinnerHitPoint - base.transform.position).sqrMagnitude;
                    if (sqrMagnitude < num)
                    {
                        num = sqrMagnitude;
                        vector = bulletDodgeProjectile2.spinnerHitPoint;
                    }
                }
            }
            if (flag)
            {
                float num2 = Mathf.Sqrt(num);
                if (num2 < 1.5f)
                {
                    float num3 = Mathf.Clamp(num2 / 1.5f, 0.1f, 0.5f);
                    this.axis.y = ((vector.x < base.transform.position.x) ? num3 : (-num3));
                }
                else
                {
                    this.axis.y = 0f;
                }
            }
            CharacterMoverInput result = new CharacterMoverInput(this.axis, this.jump, false);

            // DO MOVEMENT


            // CALCULATE VELOCITY


            // BASE DO MOVEMENT
            localpl.transform.rotation = Quaternion.Euler(0f, y, 0f);
            this.netIsGrounded.Value = this.controller.isGrounded;
            this.velocity.Value = this.mover.Velocity;
        }
    
}
   

}
}




  
}
