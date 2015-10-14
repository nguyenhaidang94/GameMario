using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public class MapObject
    {
        #region CONSTANT

        public const int COLUMN_SIZE = 32;
        public const int ROW_SIZE = 32;
        public const int MINIMUM_WIDTH = 16;
        public const int MINIMUM_HEIGHT = 16;

        #endregion

        /// <summary>
        /// list tile
        /// </summary>
        private List<TileObject> _ListGround;
        public List<TileObject> ListGround
        {
            get { return _ListGround; }
            set { _ListGround = value; }
        }

        private List<TileObject> _ListObject;
        public List<TileObject> ListObject
        {
            get { return _ListObject; }
            set { _ListObject = value; }
        }

        /// <summary>
        /// rows
        /// </summary>
        public int MapRow { get; set; }

        /// <summary>
        /// clolumn
        /// </summary>
        public int MapColumn { get; set; }

        /// <summary>
        /// width
        /// </summary>
        public int MapWidth { get; set; }

        /// <summary>
        /// height
        /// </summary>
        public int MapHeight { get; set; }

        /// <summary>
        /// constructor
        /// </summary>
        public MapObject()
        {
            _ListGround = new List<TileObject>();
            _ListObject = new List<TileObject>();
        }

        //lay enemy tai diem p
        public TileObject GetObjectAtPoint(int x, int y)
        {
            if (_ListObject.Count == 0)
                return null;

            foreach (TileObject tileObj in _ListObject)
            {
                if (tileObj.IsContainPoint(x, y))
                    return tileObj;
            }
            return null;
        }

        //lay ground tai diem p
        public TileObject GetGroundAtPoint(int x, int y)
        {
            if (_ListGround.Count == 0)
                return null;
            foreach (TileObject tileObj in _ListGround)
            {
                if (tileObj.IsContainPoint(x, y))
                return tileObj;
            }
            return null;
        }
    }
}
