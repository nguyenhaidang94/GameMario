using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public enum eOBJECTID
    { 
        ERASER,         //0
        GROUND,         //1
        BROWN_BRICK,    //2
        BLUE_BRICK,     //3
        BROWN_BLOCK,    //4
        BLUE_BLOCK,     //5
        QUEST_BLOCK,    //6
        FLAG,           //7
        LADDER,         //8
        PIPE64x64,      //9
        PIPE64x96,      //10
        PIPE64x128,     //11
        PIPE96x64,      //12
        PIPE64x256,     //13
        PIPE64x352,     //14
        COIN,           //15
        BLOCK_GROW_UP_MUSHROOM,//16
        BLOCK_LEVEL_UP_MUSHROOM,//17
        BLUE_BRICK_GROW_UP_MUSHROOM,//18
        BLUE_BRICK_LEVEL_UP_MUSHROOM,//19
        BROWN_BRICK_COIN,//20
        BLUE_BRICK_COIN,//21
        BROWN_BRICK_STAR,//22
        BLUE_BRICK_STAR,//23
        BROWN_GOOMPA,   //24
        BLUE_GOOMPA,    //25
        GREEN_PLANT,//26
        DARK_GREEN_PLANT,//27
        GREEN_TURTLE,//28
        DARK_GREEN_TURTLE,//29
        RED_TURTLE,//30
        RED_FLY_TURTLE,//31
        CONTAIN_BLOCK,  //32
        SMALL_LIFT,     //33
        GRAY_MONEY_BLOCK,//34
        AXE,            //35
        FIRE,           //36
        BOSS,           //37
        LAVA,           //38
        LINE,           //39
        BRIDGE,         //40
        RED_FLY_HIGH_TURTLE,//41
        COLUMN_FIRE,    //42
        MUSHROOM_RETAINER,//43
        PRINCESS,       //44
    }

    public class TileObject: IComparable<TileObject>
    {
        public static int FLAG_WIDTH = 4;

        private int _Id;
        public int Id
        {
            get { return _Id; }
            set { _Id = value; }
        }

        private Box _BoundaryBox;
        public Box BoundaryBox
        {
            get { return _BoundaryBox; }
            set { _BoundaryBox = value; }
        }

        private string _Note;
        public string Note
        {
            get { return _Note; }
            set { _Note = value; }
        }

        /// <summary>
        /// constructor
        /// </summary>
        public TileObject(int id, int x, int y, int width, int height)
        {
            _Id = id;
            _BoundaryBox = new Box(x, y, width, height);
        }

        /// <summary>
        /// movement range of object
        /// </summary>
        public Box MovementRangeBox 
        {
            get
            { 
                switch (_Id)
                { 
                    //case (int)eOBJECT.BROWN_GOOMPA:
                    //    break;
                    //case (int)eOBJECT.BLUE_GOOMPA:
                    //    break;
                    //case (int)eOBJECT.GREEN_TURTLE:
                    //    break;
                    //case (int)eOBJECT.DARK_GREEN_TURTLE:
                    //    break;
                    //case (int)eOBJECT.RED_TURTLE:
                    //    break;
                    //case (int)eOBJECT.RED_FLY_TURTLE:
                    //    break;
                    default:
                        return _BoundaryBox;
                }
            }
        }

        /// <summary>
        /// check box contains a point
        /// </summary>
        public bool IsContainPoint(int x, int y)
        {
            int left = _BoundaryBox.X - _BoundaryBox.Width / 2;
            int right = _BoundaryBox.X + _BoundaryBox.Width / 2;
            int top = _BoundaryBox.Y + _BoundaryBox.Height / 2;
            int bot = _BoundaryBox.Y - _BoundaryBox.Height / 2;
            if (x >= left && x <= right && y <= top && y >= bot)
                return true;
            return false;
        }

        /// <summary>
        /// get priority of tileobject
        /// which object will be in the front of list
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public static int GetPriority(int id)
        {
            int result = 0;
            switch (id)
            { 
                case (int)eOBJECTID.GROUND:
                case (int)eOBJECTID.LAVA:
                    result = 0;
                    break;
                case (int)eOBJECTID.BROWN_BRICK:
                case (int)eOBJECTID.BLUE_BRICK:
                case (int)eOBJECTID.BROWN_BLOCK:
                case (int)eOBJECTID.BLUE_BLOCK:
                case (int)eOBJECTID.QUEST_BLOCK:
                case (int)eOBJECTID.FLAG:
                case (int)eOBJECTID.BLOCK_GROW_UP_MUSHROOM:
                case (int)eOBJECTID.BLOCK_LEVEL_UP_MUSHROOM:
                case (int)eOBJECTID.BLUE_BRICK_GROW_UP_MUSHROOM:
                case (int)eOBJECTID.BROWN_BRICK_COIN:
                case (int)eOBJECTID.BLUE_BRICK_COIN:
                case (int)eOBJECTID.BROWN_BRICK_STAR:
                case (int)eOBJECTID.BLUE_BRICK_STAR:
                case (int)eOBJECTID.CONTAIN_BLOCK:
                case (int)eOBJECTID.GRAY_MONEY_BLOCK:
                    result = 1;
                    break;
                default:
                    result = 2;
                    break;
            }

            return result;
        }

        /// <summary>
        /// override function CompareTo in IComparable
        /// </summary>
        /// <returns></returns>
        public int CompareTo(TileObject other)
        {
            if (other == null)
                return -1;
            else
            {
                //conpare priority
                int priority = GetPriority(this._Id);
                int otherPriority = GetPriority(other._Id);
                if (priority < otherPriority)
                    return -1;
                else if (priority > otherPriority)
                    return 1;
                else
                { 
                    //compare position
                    int x1 = 0;
                    int y1 = 0;
                    int x2 = 0;
                    int y2 = 0;
                    switch (priority)
                    { 
                            //group GROUND, LAVA
                            //compare botleft
                        case 0:
                            x1 = this._BoundaryBox.X - this._BoundaryBox.Width/2;
                            y1 = this._BoundaryBox.Y - this._BoundaryBox.Height/2;
                            x2 = other._BoundaryBox.X - other._BoundaryBox.Width/2;
                            y2 = other._BoundaryBox.Y - other._BoundaryBox.Height / 2;
                            break;
                            //others
                            //compare middle point
                        default:
                            x1 = this._BoundaryBox.X;
                            y1 = this._BoundaryBox.Y;
                            x2 = other._BoundaryBox.X;
                            y2 = other._BoundaryBox.Y;
                            break;
                    }
                    if (x1 < x2)
                        return -1;
                    else if (x1 > x2)
                        return 1;
                    else
                    {
                        if (y1 < y2)
                            return -1;
                        else if (y1 == y2)
                            return 0;
                        else
                            return 1;
                    }
                }
            }
        }
    }
}
