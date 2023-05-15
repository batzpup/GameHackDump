﻿using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using static UnityEngine.Random;

namespace PummelPartyHacks.UI
{
    public class ItemContainers
    {
        public class ButtonContainer
        {
            private readonly Rect _loc;
            private readonly string _text;
            private readonly Action _function;


            public ButtonContainer(Rect loc, string text, Action function)
            {
                _loc = loc;
                _text = text;
                _function = function;
            }

            public void RenderControl()
            {
                if (GUI.Button(_loc, _text))
                {
                    _function();
                }
            }
        }
        public class LabelContainer
        {
            private readonly Rect _loc;
            private readonly string _text;

            public LabelContainer(Rect loc, string text)
            {
                _loc = loc;
                _text = text;
            }

            public void RenderControl()
            {
                GUI.Label(_loc, _text);
            }
        }
        public class StringFieldButtonContainer
        {
            private readonly Rect _fieldloc;
            private readonly Rect _buttonLoc;
            private string _buttontext;
            private string _inputText = "Bullet Barrage";
            private readonly Action<string> _function;

            public StringFieldButtonContainer(Rect buttonLoc, Rect fieldloc, string buttontext, Action<string> onValidUpdate)
            {
                _buttonLoc = buttonLoc;
                _fieldloc = fieldloc;
                _buttontext = buttontext;
                _function = onValidUpdate;
            }
            public void RenderControl()
            {
                _inputText = GUI.TextField(_fieldloc, _inputText);
                if (GUI.Button(_buttonLoc, _buttontext))
                {
                    _function(_inputText);
                }
            }
        }

        public class Vector2NumFieldButtonContainer
        {
            private readonly Rect[] _fieldloc = new Rect[2];
            private readonly Rect _buttonLoc;
            private string _buttontext;
            private string[] _inputTexts = new string[2] { "0", "0" };
            private readonly Action<int[]> _function;

            public Vector2NumFieldButtonContainer(Rect buttonLoc, Rect[] fieldloc, string buttontext, Action<int[]> onValidUpdate)
            {
                _buttonLoc = buttonLoc;
                _fieldloc = fieldloc;
                _buttontext = buttontext;
                _function = onValidUpdate;
            }
            public void RenderControl()
            {
                for (int i = 0; i < _fieldloc.Length; i++)
                {
                    _inputTexts[i] = GUI.TextField(_fieldloc[i], _inputTexts[i]);
                }
                if (GUI.Button(_buttonLoc, _buttontext))
                {
                    int[] vector2 = new int[2];
                    for (int i = 0; i < _inputTexts.Length; i++)
                    {
                        if (int.TryParse(_inputTexts[i], out int number))
                        {
                            vector2[i] = number;

                        }
                        else
                        {
                            return;
                        }
                    }
                    _function(vector2);
                }

            }
        }

        public class Vector3NumFieldButtonContainer
        {
            private readonly Rect[] _fieldloc = new Rect[3];
            private readonly Rect _buttonLoc;
            private string _buttontext;
            private string[] _inputTexts = new string[3] { "0", "0", "0" };
            private readonly Action<int[]> _function;

            public Vector3NumFieldButtonContainer(Rect buttonLoc, Rect[] fieldloc, string buttontext, Action<int[]> onValidUpdate)
            {
                _buttonLoc = buttonLoc;
                _fieldloc = fieldloc;
                _buttontext = buttontext;
                _function = onValidUpdate;
            }
            public void RenderControl()
            {
                for (int i = 0; i < _fieldloc.Length; i++)
                {
                    _inputTexts[i] = GUI.TextField(_fieldloc[i], _inputTexts[i]);
                }
                if (GUI.Button(_buttonLoc, _buttontext))
                {
                    int[] vector3 = new int[3];
                    for (int i = 0; i < _inputTexts.Length; i++)
                    {
                        if (int.TryParse(_inputTexts[i], out int number))
                        {
                            vector3[i] = number;

                        }
                        else
                        {
                            return;
                        }
                    }
                    _function(vector3);
                }
            }
        }

        public class NumFieldButtonContainer
        {
            private readonly Rect _fieldloc;
            private readonly Rect _buttonLoc;
            private string _buttontext;
            private string _inputText;
            private readonly Action<int> _function;

            public NumFieldButtonContainer(Rect buttonLoc, Rect fieldloc, string buttontext, Action<int> onValidUpdate)
            {
                _buttonLoc = buttonLoc;
                _fieldloc = fieldloc;
                _buttontext = buttontext;
                _function = onValidUpdate;
            }
            public void RenderControl()
            {
                _inputText = GUI.TextField(_fieldloc, _inputText);

                if (GUI.Button(_buttonLoc, _buttontext))
                {
                    if (int.TryParse(_inputText, out int number))
                    {

                        _function(number);


                    }
                }



            }

        }
        public class FloatFieldButtonContainer
        {
            private readonly Rect _fieldloc;
            private readonly Rect _buttonLoc;
            private string _buttontext;
            private string _inputText;
            private readonly Action<float> _function;

            public FloatFieldButtonContainer(Rect buttonLoc, Rect fieldloc, string buttontext, Action<float> onValidUpdate)
            {
                _buttonLoc = buttonLoc;
                _fieldloc = fieldloc;
                _buttontext = buttontext;
                _function = onValidUpdate;
            }
            public void RenderControl()
            {
                _inputText = GUI.TextField(_fieldloc, _inputText);

                if (GUI.Button(_buttonLoc, _buttontext))
                {
                    if (float.TryParse(_inputText, out float number))
                    {

                        _function(number);


                    }
                }



            }

        }

        public class ToggleContainer
        {
            private readonly Rect _loc;
            private readonly string _text;
            private readonly Action _function;
            private bool _state;

            public ToggleContainer(Rect loc, string text, Action onToggle)
            {
                _loc = loc;
                _text = text;
                _function = onToggle;
            }

            public void RenderControl()
            {
                var last = _state;
                _state = GUI.Toggle(_loc, _state, _text);
                if (_state != last)
                {
                    _function();
                }
            }
        }
        public class SliderContainer
        {
            private readonly Rect _loc;
            private readonly string _text;
            private readonly Action<float> _function;
            private float _value;
            private readonly float _min;
            private readonly float _max;
            private readonly float _increment;

            public SliderContainer(Rect loc, string text, float min, float max,
                Action<float> onAdjust,
                float @default = float.NaN, float increment = 0.01f)
            {
                _loc = loc;
                _text = text;
                _min = min;
                _max = max;
                _function = onAdjust;
                _increment = increment;
                _value = !float.IsNaN(@default) ? @default : min;
            }

            public void RenderControl()
            {
                var last = _value;
                GUI.Label(_loc, $"{_text}: {_value:F2}");
                Rect slidePos = new Rect(_loc);
                slidePos.y += slidePos.height;
                _value = GUI.HorizontalSlider(
                         slidePos,
                    _value,
                    _min,
                    _max);
                if (Math.Abs(_value - last) > 0.001)
                {
                    _value = (float)Math.Round(_value / _increment) * _increment;
                    _function(_value);
                }
            }
        }


        public class ObjectScrollContainer
        {
            private readonly Rect _loc;
            private readonly string _text;
            private List<GameObject> _items;
            private readonly Action<GameObject> _function;
            private Vector2 _scrollPosition = Vector2.zero;
            private int _padding;
            private int _controlHeight;


            public ObjectScrollContainer(Rect loc, string text, List<GameObject> items, Action<GameObject> function, int padding = 5, int controlHeight = 20)
            {
                _loc = loc;
                _text = text;
                _items = items;
                _function = function;
                _padding = padding;
                _controlHeight = controlHeight;
            }

            public void RenderControl()
            {
                GUI.Label(new Rect(_loc.x, _loc.y, _loc.width, _controlHeight), _text);
                _scrollPosition = GUI.BeginScrollView(new Rect(_loc.x, _loc.y + (_controlHeight + _padding), _loc.width, _loc.height), _scrollPosition, new Rect(0, 0, 0, (_controlHeight + _padding) * _items.Count));
                foreach (var item in _items.Select((value, index) => new { index, value }))
                {
                    if (item.value is null)
                    {
                        GUI.Label(new Rect(0, (_controlHeight + _padding) * item.index, _loc.width, _controlHeight), $"Item {item.index} Unloaded");
                        continue;
                    }

                    if (GUI.Button(new Rect(0, (_controlHeight + _padding) * item.index, _loc.width, _controlHeight), $"{item.value.name} [{item.value.tag}]"))
                    {
                        _function(item.value);
                    }
                }
                GUI.EndScrollView();
            }




        }

        
    }
}


/*
 scroll window
 //  GUI.Label(new Rect(100, 100, 300, 100), ConsoleInterface.PassedStr);
          
          scrollPosition = GUI.BeginScrollView(new Rect(10, 300, 200, 100), scrollPosition, new Rect(0, 0, 180, 200));

          // Make four buttons - one in each corner. The coordinate system is defined
          // by the last parameter to BeginScrollView.
          GUI.Button(new Rect(0, 0, 180, 20), "A");
          GUI.Button(new Rect(0, 25, 180, 20), "b");
          GUI.Button(new Rect(0, 50, 180, 20), "c");
          GUI.Button(new Rect(0, 75, 180, 20), "d");
          GUI.Button(new Rect(0, 100, 180, 20), "e");
          GUI.Button(new Rect(0, 125, 180, 20), "f");
          GUI.Button(new Rect(0, 150, 180, 20), "g");
          GUI.Button(new Rect(0, 175, 180, 20), "h");
          GUI.Button(new Rect(0, 200, 180, 20), "i");

          // End the scroll view that we began above.
          GUI.EndScrollView();
*/



// foreach (var buttonContainer in _buttons)
// {
//     buttonContainer.RenderControl();
// }