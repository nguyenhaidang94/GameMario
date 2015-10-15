#pragma once
#include "DynamicGameObject.h"
#include "SwepAABB.h"
#include <vector>

class Node
{
private:
	int _NodeId;
	int _X;
	int _Y;
	int _Width;
	int _Height;
	
public:
	Node* _Tl;
	Node* _Tr;
	Node* _Bl;
	Node* _Br;
	std::vector<GameObject*> _ListObjects;

	Node(int nodeId, int x, int y, int w, int h);
	Box GetBoundaryBox();
	void Release();
	~Node();
};

