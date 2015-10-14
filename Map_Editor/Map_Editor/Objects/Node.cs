using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Map_Editor.Objects
{
    public enum REGION
    { 
        TOP_LEFT    = 1,
        TOP_RIGHT   = 2,
        BOT_LEFT    = 3,
        BOT_RIGHT   = 4
    }

    public class Node
    {
        #region CONSTANT

        public const int SCREEN_WIDTH = 480;
        public const int SCREEN_HEIGHT = 480;

        #endregion


        //node top left
        private Node _Tl;
        public Node Tl
        {
            get { return _Tl; }
            set { _Tl = value; }
        }

        //node top right
        private Node _Tr;
        public Node Tr
        {
            get { return _Tr; }
            set { _Tr = value; }
        }

        //node bot left
        private Node _Bl;
        public Node Bl
        {
            get { return _Bl; }
            set { _Bl = value; }
        }

        //node bot right
        private Node _Br;
        public Node Br
        {
            get { return _Br; }
            set { _Br = value; }
        }

        //id node
        private int _NodeId;
        public int NodeId
        {
            get { return _NodeId; }
            set { _NodeId = value; }
        }

        //region: tl, tr, bl, br
        private REGION _Region;
        public REGION Region
        {
            get { return _Region; }
            set { _Region = value; }
        }

        //boundarybox
        private Box _BoundaryBox;
        public Box BoundaryBox
        {
            get { return _BoundaryBox; }
            set { _BoundaryBox = value; }
        }

        //list objects it contains
        //only leafnode can contain objects
        private List<TileObject> _ListObject;
        public List<TileObject> ListObject
        {
            get { return _ListObject; }
            set { _ListObject = value; }
        }

        /// <summary>
        /// constructor
        /// </summary>
        public Node(int parentNodeId, REGION region, Box boundaryBox)
        {
            _Tl = null;
            _Tr = null;
            _Bl = null;
            _Br = null;

            _Region = region;
            _NodeId = parentNodeId * 10 + (int)_Region;
            _ListObject = new List<TileObject>();
            //node root
            if (parentNodeId == 0)
                _BoundaryBox = boundaryBox;
            else
            {
                switch (_Region)
                { 
                    case REGION.TOP_LEFT:
                        _BoundaryBox = new Box(
                            boundaryBox.X - boundaryBox.Width/4,
                            boundaryBox.Y + boundaryBox.Height/4,
                            boundaryBox.Width/2,
                            boundaryBox.Height/2
                            );
                        break;
                    case REGION.TOP_RIGHT:
                        _BoundaryBox = new Box(
                            boundaryBox.X + boundaryBox.Width / 4,
                            boundaryBox.Y + boundaryBox.Height / 4,
                            boundaryBox.Width / 2,
                            boundaryBox.Height / 2
                            );
                        break;
                    case REGION.BOT_LEFT:
                        _BoundaryBox = new Box(
                            boundaryBox.X - boundaryBox.Width / 4,
                            boundaryBox.Y - boundaryBox.Height / 4,
                            boundaryBox.Width / 2,
                            boundaryBox.Height / 2
                            );
                        break;
                    case REGION.BOT_RIGHT:
                        _BoundaryBox = new Box(
                            boundaryBox.X + boundaryBox.Width / 4,
                            boundaryBox.Y - boundaryBox.Height / 4,
                            boundaryBox.Width / 2,
                            boundaryBox.Height / 2
                            );
                        break;
                }
            }
        }

        /// <summary>
        /// insert node
        /// </summary>
        public static void InsertNode(Node node, TileObject obj)
        {
            //if object doesn't belong to node, then return
            if (!Box.IsIntersect(node.BoundaryBox, obj.MovementRangeBox))
                return;

            //if node covers all screenhight and screenwidth, then divide it into 4 subnodes
            if (node.BoundaryBox.Width >= SCREEN_WIDTH + 6 && node.BoundaryBox.Height >= SCREEN_HEIGHT + 6)
            {
                if (node._Tl == null)
                    node._Tl = new Node(node._NodeId, REGION.TOP_LEFT, node.BoundaryBox);
                if (node._Tr == null)
                    node._Tr = new Node(node._NodeId, REGION.TOP_RIGHT, node.BoundaryBox);
                if (node._Bl == null)
                    node._Bl = new Node(node._NodeId, REGION.BOT_LEFT, node.BoundaryBox);
                if (node._Br == null)
                    node._Br = new Node(node._NodeId, REGION.BOT_RIGHT, node.BoundaryBox);

                //insert each subnode to node
                InsertNode(node._Tl, obj);
                InsertNode(node._Tr, obj);
                InsertNode(node._Bl, obj);
                InsertNode(node._Br, obj);
            }
            //else if node just covers enough screenwidth or screenheight, then add obj to node
            else
                node.ListObject.Add(obj);
        }
    }
}
