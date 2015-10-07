using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public class TileObject
    {
        private int _Id;
        public int Id
        {
            get { return _Id; }
            set { _Id = value; }
        }

        private Point _TilePoint;
        public Point TilePoint
        {
            get { return _TilePoint; }
            set { _TilePoint = value; }
        }

        private Size _TileSize;
        public Size TileSize
        {
            get { return _TileSize; }
            set { _TileSize = value; }
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
        public TileObject(int id, Point point, Size size)
        {
            _Id = id;
            _TilePoint = point;
            _TileSize = size;
        }
    }
}
