#pragma once
#include "DynamicGameObject.h"
#include "SwepAABB.h"
#include <vector>

class Node
{
private:
	int _NodeId;		//node id
	int _X;				//position X
	int _Y;				//position Y
	int _Width;			//node width
	int _Height;		//node height
	Box _BoundaryBox;	//boundarybox
	
public:
	Node* _Tl;			//subnode topleft
	Node* _Tr;			//subnode topright
	Node* _Bl;			//subnode botleft
	Node* _Br;			//subnode botright
	std::vector<GameObject*> _ListObjects;	//listobject in node

	//constructor
	Node(int nodeId, int x, int y, int w, int h);
	//check if node is empty or not
	bool IsEmpty();
	//get nodeid
	int GetNodeId();
	//get boundarybox
	Box GetBoundaryBox();
	//insert object to node
	void InsertObject(std::map<int, Node*> mapQuadTree, GameObject* object, Box objectBox);
	//release node
	void Release();
	//destructor
	~Node();
};

