
using PummelPartyHacks.Utilities;
using System;
using System.Reflection;
using UnityEngine;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class MortarMayhemHelper : MinigameHelper
    {
        

        
        MortarMayhemPlayer _localMortarMayhemPlayer;
        
        GameObject cube;
        Vector3 posAtNewDestSpawn = Vector3.zero;
        Vector3 targetPosition;
        Vector3 oldtargetPosition = Vector3.zero;
        


        MortarMayhemController minigameController;
        CharacterMover mover;
        CharacterController controller;
        PlayerAnimation playerAnim;
        Vector3 moveVector = Vector3.zero;


        Vector3 moverVelocity;
        Vector3 moveVectorNomalized;
        Vector3 oldVelocity = Vector3.zero;
        
        

        public void HandleMortarMayhem()
        {
            if (_localMortarMayhemPlayer == null)
            {
                foreach (var mortarMayhemPlayer in FindObjectsOfType<MortarMayhemPlayer>())
                {
                    if (mortarMayhemPlayer.GamePlayer.IsLocalPlayer && !mortarMayhemPlayer.GamePlayer.IsAI)
                    {
                        _localMortarMayhemPlayer = mortarMayhemPlayer;
                        break;
                    }
                }

            }
            
            if(hackMain.b_HandleCurrentMinigame)
            {
                if (cube == null)
                {
                    cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
                    cube.GetComponent<BoxCollider>().enabled = false;
                    
                }
            }
            

             minigameController = (MortarMayhemController)_localMortarMayhemPlayer.GetType().GetField("minigameController", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(_localMortarMayhemPlayer);
             mover = (CharacterMover)_localMortarMayhemPlayer.GetType().GetField("mover", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(_localMortarMayhemPlayer);
             controller = (CharacterController)mover.GetType().GetField("controller", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(mover);
             playerAnim = (PlayerAnimation)_localMortarMayhemPlayer.GetType().BaseType.GetField("playerAnim", BindingFlags.NonPublic | BindingFlags.Instance).GetValue(_localMortarMayhemPlayer);
             //ConsoleBase.WriteLine(" natural Velocity " +mover.Velocity.ToString());
            if (minigameController != null)
            {
                //Calaculations
                

                targetPosition = minigameController.GetGridPos((int)_localMortarMayhemPlayer.OwnerSlot, minigameController.curX[(int)_localMortarMayhemPlayer.OwnerSlot], minigameController.curY[(int)_localMortarMayhemPlayer.OwnerSlot]);
                if (hackMain.b_HandleCurrentMinigame)
                {
                    cube.transform.position = targetPosition;
                }
                else if (cube != null)
                {
                   Destroy(cube.gameObject,0f);
                }
                
                if (hackMain.b_SuperCheats)
                {

                    if(oldtargetPosition != targetPosition)
                    {
                        //ConsoleBase.WriteLine("Target updated");
                        posAtNewDestSpawn = _localMortarMayhemPlayer.transform.position;
                        oldtargetPosition = targetPosition;
                      


                    }
                    moveVector = targetPosition - _localMortarMayhemPlayer.transform.position;
                    moveVector.y = 0;

                    if (Mathf.Abs(moveVector.x) < 0.15f)
                    {
                        //ConsoleBase.WriteLine("Stopping close enough");
                        moveVector.x = 0;
                    }
                    if (Mathf.Abs(moveVector.z) < 0.15f)
                    {
                       // ConsoleBase.WriteLine("Stopping close enough");
                        moveVector.z = 0;
                    }
                    // Update controller replacement
                    // Do Movement Replacement
                    //calculate velocity replacement
                    CalculateVelocity(Time.deltaTime);
                    
                        //--- End of Calculate Velocity
                    mover.DoMovement(Time.deltaTime);
                    mover.SmoothSlope();
                    if (mover.Velocity != Vector3.zero)
                    {
                        _localMortarMayhemPlayer.transform.rotation = Quaternion.RotateTowards(_localMortarMayhemPlayer.transform.rotation, Quaternion.LookRotation(moveVector), 1500f * Time.deltaTime);
                    }
                    _localMortarMayhemPlayer.velocity.Value = mover.Velocity;
                    _localMortarMayhemPlayer.netIsGrounded.Value = mover.Grounded;
                    //--- End of DoMovement


                    _localMortarMayhemPlayer.rotation.Value = _localMortarMayhemPlayer.transform.rotation.eulerAngles.y;
                    _localMortarMayhemPlayer.position.Value = _localMortarMayhemPlayer.transform.position;
                    if (playerAnim != null)
                    {
                        //_localMortarMayhemPlayer.UpdateAnimationState(playerAnim);
                        MethodInfo dynMethod = _localMortarMayhemPlayer.GetType().GetMethod("UpdateAnimationState", BindingFlags.NonPublic | BindingFlags.Instance);
                        var result = dynMethod.Invoke(_localMortarMayhemPlayer, new object[] { playerAnim });
                        playerAnim.UpdateAnimationState();
                    }
                    else
                    {
                        //ConsoleBase.WriteLine("Player Anim is null");
                    }
                }
            }

            else
            {
                //ConsoleBase.WriteLine("minigameController is null");
                if (cube != null)
                {
                    Destroy(cube.gameObject, 0f);
                }
            }


        }
        // Todo Replicate add 0.5f velocity per frame until you reach 6, same with decelleration
        private void CalculateVelocity(float deltaTime)
        {
            
            moverVelocity = (Vector3)mover.GetType().GetField("velocity",BindingFlags.NonPublic|BindingFlags.Instance).GetValue(mover);
            moverVelocity.y = 0;
            moveVectorNomalized = new Vector3(0, 0, 0);
            moveVectorNomalized += moveVector;
            moveVectorNomalized.Normalize();
            float stepSize = UnityEngine.Random.Range(0.2f, 0.3f);

            if(Mathf.Abs( Vector3.Distance(targetPosition,_localMortarMayhemPlayer.transform.position)) < Mathf.Abs(Vector3.Distance(targetPosition, posAtNewDestSpawn)/2))
            {
               //ConsoleBase.WriteLine("Ive past half way slowing down");
               // ConsoleBase.WriteLine("old stepsize: " + stepSize.ToString());
                stepSize *= -1;
               // ConsoleBase.WriteLine("new stepsize: " + stepSize.ToString());
            }
    
               
            
      
            if (Math.Sign(moveVectorNomalized.x) > 0 && oldVelocity.x < 6f)
            {
                oldVelocity.x += stepSize;
            }
            else if(Math.Sign(moveVectorNomalized.x) < 0 && oldVelocity.x > -6f)
            {
                oldVelocity.x -= stepSize;
            }
            else
            {
                oldVelocity.x = 0;
            }
            if (Math.Sign(moveVectorNomalized.z) > 0 && oldVelocity.z < 6f)
            {
                oldVelocity.z += stepSize;
            }
            else if (Math.Sign(moveVectorNomalized.z) < 0 && oldVelocity.z > -6f)
            {
                oldVelocity.z -= stepSize;
            }
            else
            {
                oldVelocity.z = 0;
            }
            moverVelocity = oldVelocity;

            mover.GetType().GetField("controlMovement", BindingFlags.NonPublic | BindingFlags.Instance).SetValue(mover,moveVectorNomalized);
            mover.GetType().GetField("velocity", BindingFlags.NonPublic | BindingFlags.Instance).SetValue(mover, moverVelocity);
            //ConsoleBase.WriteLine(" new Velocity" + moverVelocity.ToString());


        }
    }
}
