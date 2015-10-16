#include "Node.h"


Node::Node(int nodeId, int x, int y, int w, int h)
{
	_NodeId = nodeId;
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;
	_BoundaryBox =  Box(_X - _Width / 2, _Y + _Height / 2, _Width, _Height);

	_Tl = NULL;
	_Tr = NULL;
	_Bl = NULL;
	_Br = NULL;
}

int Node::GetNodeId()
{
	return _NodeId;
}

Box Node::GetBoundaryBox()
{
	return _BoundaryBox;
}

void Node::InsertObject(GameObject* object, Box objectBox)
{
	//if object doesn't belong to node, then return
	if (!AABBCheck(_BoundaryBox, objectBox))
		return;

	//if node covers all screenhight and screenwidth, then divide it into 4 subnodes
	if (_BoundaryBox.fWidth >= SCREEN_WIDTH + 6 && _BoundaryBox.fHeight >= SCREEN_HEIGHT + 6)
	{
		if (_Tl == NULL)
			_Tl = new Node(
				_NodeId * 10 + eNodePosition::eTopLeft,
				_X - _Width / 4,
				_Y + _Height / 4,
				_Width / 2,
				_Height / 2
			);
		if (_Tr == NULL)
			_Tr = new Node(
				_NodeId * 10 + eNodePosition::eTopRight,
				_X + _Width / 4,
				_Y + _Height / 4,
				_Width / 2,
				_Height / 2
			);
		if (_Bl == NULL)
			_Bl = new Node(
				_NodeId * 10 + eNodePosition::eBotLeft,
				_X - _Width / 4,
				_Y - _Height / 4,
				_Width / 2,
				_Height / 2
			);
		if (_Br == NULL)
			_Br = new Node(
				_NodeId * 10 + eNodePosition::eBotRight,
				_X + _Width / 4,
				_Y - _Height / 4,
				_Width / 2,
				_Height / 2
			);

		float left, right, top, bot;
		left = objectBox.fX;
		right = objectBox.fX + objectBox.fWidth;
		top = objectBox.fY;
		bot = objectBox.fY - objectBox.fHeight;
		//if object places in two diagonals, then add it to node
		if ((left <= _X && right >= _X)
			|| (bot <= _Y && top >= _Y))
		{
			_ListObjects.push_back(object);
		}
		else
		{
			//insert each subnode to node
			_Tl->InsertObject(object, objectBox);
			_Tr->InsertObject(object, objectBox);
			_Bl->InsertObject(object, objectBox);
			_Br->InsertObject(object, objectBox);
		}
	}
	//else if node just covers enough screenwidth or screenheight, then add obj to node
	else
		_ListObjects.push_back(object);
}

void Node::Release()
{
	_ListObjects.clear();
}

Node::~Node()
{
}
