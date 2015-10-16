using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public class Box
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

        private int _Width;
        public int Width
        {
            get { return _Width; }
            set { _Width = value; }
        }

        private int _Height;
        public int Height
        {
            get { return _Height; }
            set { _Height = value; }
        }

        public Box(int x, int y, int width, int height)
        {
            _X = x;
            _Y = y;
            _Width = width;
            _Height = height;
        }

        //check two boxs are intersect
        public static bool IsIntersect(Box box1, Box box2)
        {
            if (box2.X + box2.Width/2 <= box1.X - box1.Width/2      //box2 nam ben trai box1
                || box2.X - box2.Width/2 >= box1.X + box1.Width/2   //box2 nam ben phai box1)
                || box2.Y - box2.Height/2 >= box1.Y + box1.Height/2 //box2 nam ben tren box1
                || box2.Y + box2.Height/2 <= box1.Y - box1.Height/2)//box2 nam ben duoi box 1      
                return false;
            return true;
        }
    }
}
