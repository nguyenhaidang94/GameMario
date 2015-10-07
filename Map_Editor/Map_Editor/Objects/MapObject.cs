using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public struct ENEMY_INFO
    {
        private int _X;
        public int X
        {
            get { return _X; }
            set { _X = value; }
        }

        private int _Y;
        public int Y
        {
            get { return _Y; }
            set { _Y = value; }
        }

        private int _Id;
        public int Id
        {
            get { return _Id; }
            set { _Id = value; }
        }

        public ENEMY_INFO(int x, int y, int id)
        {
            this._X = x;
            this._Y = y;
            this._Id = id;
        }
    }

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

        private List<TileObject> _ListEnemy;
        public List<TileObject> ListEnemy
        {
            get { return _ListEnemy; }
            set { _ListEnemy = value; }
        }

        /// <summary>
        /// arr tile number
        /// </summary>
        public int[][] ArrTileNumber;

        /// <summary>
        /// rows
        /// </summary>
        public int MapRow;

        /// <summary>
        /// clolumn
        /// </summary>
        public int MapColumn;

        /// <summary>
        /// constructor
        /// </summary>
        public MapObject()
        {
            _ListGround = new List<TileObject>();
            _ListEnemy = new List<TileObject>();
        }

        //lay enemy tai diem p
        public TileObject GetEnemyAtPoint(System.Drawing.Point p)
        {
            if (_ListEnemy.Count == 0)
                return null;

            foreach (TileObject tileObj in _ListEnemy)
            {
                System.Drawing.Rectangle r = new System.Drawing.Rectangle(
                    new System.Drawing.Point(
                        tileObj.TilePoint.X - tileObj.TileSize.Width/2,
                        tileObj.TilePoint.Y - tileObj.TileSize.Height/2),
                    tileObj.TileSize
                    );
                if (r.Contains(p))
                    return tileObj;
            }
            return null;
        }

        //lay ground tai diem p
        public TileObject GetGroundAtPoint(System.Drawing.Point p)
        {
            if (_ListGround.Count == 0)
                return null;
            foreach (TileObject tileObj in _ListGround)
            {
                System.Drawing.Rectangle r = new System.Drawing.Rectangle(
                    new System.Drawing.Point(
                        tileObj.TilePoint.X - tileObj.TileSize.Width / 2,
                        tileObj.TilePoint.Y - tileObj.TileSize.Height / 2),
                    tileObj.TileSize
                    );
                if (r.Contains(p))
                    return tileObj;
            }
            return null;
        }
    }
}
