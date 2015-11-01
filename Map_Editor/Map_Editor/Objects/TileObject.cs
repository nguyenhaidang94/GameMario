using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public enum eOBJECT
    { 
        ERASER,
        GROUND,
        BROWN_BRICK,
        BLUE_BRICK,
        BROWN_BLOCK,
        BLUE_BLOCK,
        QUEST_BLOCK,
        FLAG,
        LADDER,
        PIPE64x64,
        PIPE64x96,
        PIPE64x128,
        PIPE96x64,
        PIPE64x256,
        PIPE64x352,
        COIN,
        BLOCK_GROW_UP_MUSHROOM,
        BLOCK_LEVEL_UP_MUSHROOM,
        BLUE_BRICK_GROW_UP_MUSHROOM,
        BLUE_BRICK_LEVEL_UP_MUSHROOM,
        BROWN_BRICK_COIN,
        BLUE_BRICK_COIN,
        BROWN_BRICK_STAR,
        BLUE_BRICK_STAR,
        BROWN_GOOMPA,
        BLUE_GOOMPA,
        GREEN_PLANT,
        DARK_GREEN_PLANT,
        GREEN_TURTLE,
        DARK_GREEN_TURTLE,
        RED_TURTLE,
        RED_FLY_TURTLE,
    }

    public class TileObject
    {
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
    }
}
