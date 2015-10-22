#pragma once
#include "Node.h"
#include <sstream>
#include <fstream>
#include "Ground.h"
#include "Pipe.h"
#include "Brick.h"
#include "ItemBrick.h"
#include "QuestionBlock.h"
#include "HardBlock.h"
#include "Coin.h"

class QuadTree
{
private:
	static QuadTree* _Instance;
	Node* _RootNode;
	std::vector<GameObject*> _ObjectsOnScreen;
public:
	static QuadTree* GetInstance();
	QuadTree();
	void BuildQuadTree(eWorldID mapID);
	void InsertObject(GameObject* object, Box objBox);
	void RetrieveObjectsInNode(Node* node, Box sightBox);
	void UpdateObjectsOnScreen();
	std::vector<GameObject*> GetObjectsOnScreen();
	void ClearNode(Node* node);
	void Release();
	~QuadTree();
};

