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

bool Node::IsEmpty()
{
	if (_Tl != NULL || _Tr != NULL || _Bl != NULL || _Br != NULL)
		return false;
	return true;
}

int Node::GetNodeId()
{
	return _NodeId;
}

Box Node::GetBoundaryBox()
{
	return _BoundaryBox;
}

void Node::InsertObject(std::map<int, Node*> mapQuadTree, GameObject* object, Box objectBox)
{
	//if object doesn't belong to node, then return
	if (!AABBCheck(_BoundaryBox, objectBox))
		return;

	//if node covers all screenhight and screenwidth, then divide it into 4 subnodes
	if (_BoundaryBox.fWidth >= SCREEN_WIDTH + 6 && _BoundaryBox.fHeight >= SCREEN_HEIGHT + 6)
	{
		if (_Tl == NULL)
		{
			_Tl = new Node(
				_NodeId * 10 + eNodePosition::eTopLeft,
				_X - _Width / 4,
				_Y + _Height / 4,
				_Width / 2,
				_Height / 2
				);
			mapQuadTree[_Tl->GetNodeId()] = _Tl;
		}
		if (_Tr == NULL)
		{
			_Tr = new Node(
				_NodeId * 10 + eNodePosition::eTopRight,
				_X + _Width / 4,
				_Y + _Height / 4,
				_Width / 2,
				_Height / 2
				);
			mapQuadTree[_Tr->GetNodeId()] = _Tr;
		}
		if (_Bl == NULL)
		{
			_Bl = new Node(
				_NodeId * 10 + eNodePosition::eBotLeft,
				_X - _Width / 4,
				_Y - _Height / 4,
				_Width / 2,
				_Height / 2
				);
			mapQuadTree[_Bl->GetNodeId()] = _Bl;
		}
		if (_Br == NULL)
		{
			_Br = new Node(
				_NodeId * 10 + eNodePosition::eBotRight,
				_X + _Width / 4,
				_Y - _Height / 4,
				_Width / 2,
				_Height / 2
				);
			mapQuadTree[_Br->GetNodeId()] = _Br;
		}

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
			_Tl->InsertObject(mapQuadTree, object, objectBox);
			_Tr->InsertObject(mapQuadTree, object, objectBox);
			_Bl->InsertObject(mapQuadTree, object, objectBox);
			_Br->InsertObject(mapQuadTree, object, objectBox);
		}
	}
	//else if node just covers enough screenwidth or screenheight, then add obj to node
	else
		_ListObjects.push_back(object);
}

void Node::Release()
{
	while (_ListObjects.size() > 0)
	{
		std::vector<GameObject*>::iterator itr = _ListObjects.begin();
		(*itr)->Release();
		delete (*itr);
		(*itr) = NULL;
		_ListObjects.erase(itr);
	}
}

Node::~Node()
{
}
