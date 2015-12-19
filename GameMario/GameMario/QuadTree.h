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
#include "FloatingBar.h"
#include "Flagpole.h"
#include "Goomba.h"
#include "KoopaTroopa.h"
#include "KoopaParatroopa.h"
#include "PiranhaPlant.h"
#include "KingBowser.h"
#include "BulletFire.h"

class QuadTree
{
private:
	//root node
	Node* _RootNode;
	//object on screen
	std::vector<GameObject*> _ObjectsOnScreen;
	//dictionary datatype, used to browse node through it's id
	std::map<int, Node*> _MapQuadTree;
public:
	//constructor
	QuadTree();
	//read file and build quadtree
	void BuildQuadTree(eWorldID mapID);
	//insert object to quadtree
	void InsertObject(GameObject* object, Box objBox, int &returnNodeId);
	//retrieve objects in node
	void UpdateObjectsInNode(Node* node, Box sightBox);
	//update object on screen
	void UpdateObjectsOnScreen();
	//return objects on screen
	std::vector<GameObject*> GetObjectsOnScreen() const;
	//delete subnode
	void DeleteSubnode(Node *node);
	//delete node
	void DeleteNode(Node* node);
	//realease quadtree
	void Release();
	//destructor
	~QuadTree();
};

