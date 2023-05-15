using PummelPartyHacks.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

namespace PummelPartyHacks.src.Utilities
{
    partial class Helpers : MonoBehaviour
    {
        private void Start()
        {
            greenTexture = new Texture2D(2, 2, TextureFormat.ARGB32, false);
            greenTexture.SetPixel(0, 0, Color.green);
            greenTexture.SetPixel(1, 0, Color.green);
            greenTexture.SetPixel(0, 1, Color.green);
            greenTexture.SetPixel(1, 1, Color.green);
            greenTexture.Apply();
            redTexture = new Texture2D(2, 2, TextureFormat.ARGB32, false);
            redTexture.SetPixel(0, 0, Color.red);
            redTexture.SetPixel(1, 0, Color.red);
            redTexture.SetPixel(0, 1, Color.red);
            redTexture.SetPixel(1, 1, Color.red);
            redTexture.Apply();

            ConsoleBase.WriteLine("Texture initialised");

        }

        public static Texture2D greenTexture;
        public static Texture2D redTexture;
        public static Material LineMaterial;
        static Rect lineRect = new Rect(0f, 0f, 1f, 1f);

        public static void RectFilled(float x, float y, float width, float height, Texture2D text)
        {
            GUI.DrawTexture(new Rect(x, y, width, height), text);
        }

        // Token: 0x06000005 RID: 5 RVA: 0x00002178 File Offset: 0x00000378
        public static void RectOutlined(float x, float y, float width, float height, Texture2D text, float thickness = 1f)
        {
            Helpers.RectFilled(x, y, thickness, height, text);
            Helpers.RectFilled(x + width - thickness, y, thickness, height, text);
            Helpers.RectFilled(x + thickness, y, width - thickness * 2f, thickness, text);
            Helpers.RectFilled(x + thickness, y + height - thickness, width - thickness * 2f, thickness, text);
        }

        // Token: 0x06000006 RID: 6 RVA: 0x000021DC File Offset: 0x000003DC
        public static void Box(float x, float y, float width, float height, Texture2D text, float thickness = 1f)
        {
            Helpers.RectOutlined(x - width / 2f, y - height, width, height, text, thickness);
        }
    }
}
