#include "Node.h"


Node::Node(int nodeId, int x, int y, int w, int h)
{
	_NodeId = nodeId;
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;

	_Tl = NULL;
	_Tr = NULL;
	_Bl = NULL;
	_Br = NULL;
}

Box Node::GetBoundaryBox()
{
	return Box(_X - _Width / 2, _Y + _Height / 2, _Width, _Height);
}

void Node::Release()
{
	_ListObjects.clear();
}

Node::~Node()
{
}
