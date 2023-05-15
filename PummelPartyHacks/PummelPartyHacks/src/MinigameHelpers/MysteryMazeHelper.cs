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
    public class MysteryMazeHelper : MinigameHelper
    {
       
        MysteryMazeController controller;
        
     
        public void HandleMysteryMaze()
        {
            
            if (controller == null)
            {
                controller = FindObjectOfType<MysteryMazeController>();
            }
            else
            {
                
                controller.GetType().GetField("m_clipRadius", BindingFlags.NonPublic | BindingFlags.Instance).SetValue(controller, 4000f);
                
                
            }
            


        }
        
    }
}
