using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace PummelPartyHacks.src.MinigameHelpers
{
    public class MinigameHelper : MonoBehaviour
    {
        protected HackMain hackMain;


        public virtual void Init(HackMain main)
        {
            hackMain = main;
        }

    }
}
