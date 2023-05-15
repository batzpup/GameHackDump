using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using System.Reflection;

namespace PummelPartyHacks.src.Utilities
{


    partial class Helpers : MonoBehaviour
    {
        public static FieldInfo GetPrivateNonStaticField(object instance, string fieldName)
        {
            return instance.GetType().GetField(fieldName, BindingFlags.NonPublic | BindingFlags.Instance);
        }
        public static MethodInfo GetPrivateNonStaticMethod(object instance, string methodName)
        {
            return instance.GetType().GetMethod(methodName, BindingFlags.NonPublic | BindingFlags.Instance);
        }
    }
}