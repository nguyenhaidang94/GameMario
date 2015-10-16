#pragma once
#include "Node.h"
#include <sstream>
#include <fstream>
#include "Mario.h"
#include "Ground.h"
#include "Pipe.h"
#include "Brick.h"
#include "ItemBrick.h"
#include "QuestionBlock.h"
#include "HardBlock.h"

class QuadTree
{
private:
	static QuadTree* _Instance;
	Node* _RootNode;
	std::map<int, Node*> _MapQuadTree;
	std::vector<GameObject*> _ObjectsOnScreen;
public:
	static QuadTree* GetInstance();
	QuadTree();
	void BuildQuadTree(eWorldID mapID);
	void RetrieveObjectsInNode(Node* node, Box sightBox);
	void UpdateObjectsOnScreen();
	std::vector<GameObject*> GetObjectsOnScreen();
	void Clear(Node* node);
	void Release();
	~QuadTree();
};

