#include "QuadTree.h"

QuadTree::QuadTree()
{
	_RootNode = NULL;
}

void QuadTree::BuildQuadTree(eWorldID mapID)
{
	if (_MapQuadTree.size() > 0)
		_MapQuadTree.clear();
	_RootNode = NULL;

	string fileName;
	switch (mapID)
	{
	case e1_1:
		fileName = "1_1_quadtree";
		break;
	case e1_2:
		fileName = "1_2_quadtree";
		break;
	case e1_3:
		fileName = "1_3_quadtree";
		break;
	case e1_4:
		fileName = "1_4_quadtree";
		break;
	case eHidden1_1:
		fileName = "1_1_hidden_quadtree";
		break;
	case eLeft1_2:
		fileName = "1_2_left_quadtree";
		break;
	case eRight1_2:
		fileName = "1_2_right_quadtree";
		break;
	case eHidden1_2:
		fileName = "1_2_hidden_quadtree";
		break;
	default:
		break;
	}
	char quadtreeFilePath[100];
	sprintf(quadtreeFilePath, "resources\\MapObjects\\%s.txt", fileName.c_str());	//Merge string
	ifstream file(quadtreeFilePath);
	string strNodeInfo;
	while (getline(file, strNodeInfo))
	{
		//read node info
		istringstream issReadNode(strNodeInfo);
		int nodeId, nodePosX, nodePosY, nodeWidth, nodeHeight, numOfObjects;
		issReadNode >> nodeId >> nodePosX >> nodePosY >> nodeWidth >> nodeHeight >> numOfObjects;
		{
			int parentId = nodeId / 10;
			if (_MapQuadTree.find(nodeId) == _MapQuadTree.end()
				&& (parentId == 0 || _MapQuadTree.find(parentId) != _MapQuadTree.end()))
			{
				Node* node = new Node(nodeId, nodePosX, nodePosY, nodeWidth, nodeHeight);
				for (int i = 0; i < numOfObjects; i++)
				{
					//read object info
					string strObjectInfo;
					getline(file, strObjectInfo);
					istringstream issReadObj(strObjectInfo);
					int objectID, x, y, w, h;
					string tag;
					issReadObj >> objectID >> x >> y >> w >> h >> tag;
					//----------------
					//Do something with data like create object
					//Ex: _ListObject.push_back(new SomeObject(OjbectID, a, b, c));
					switch (objectID)
					{
					//Case ground
					case 1:
						node->_ListObjects.push_back(new Ground(x, y, w, h));
						break;

					//Case brick
					case 2:	//brown normal
					case 3:	//blue normal
						node->_ListObjects.push_back(new Brick(objectID, x, y));
						break;
					//Case hard block
					case 4:
					case 5:
					case 32:	//plant block in map 1_4
						node->_ListObjects.push_back(new HardBlock(objectID, x, y));
						break;
					
					//case flagpole
					case 7:
						node->_ListObjects.push_back(new Flagpole(x, y));
						break;

					//case floating bar
					case 8:
					case 33:	//small bar
						node->_ListObjects.push_back(new FloatingBar(x, y, w, h,tag));
						break;
					//Case pipe
					case 9:		//small
					case 10:	//medium
					case 11:	//big
					case 12:	//horizontal
					case 13:	//tall
					case 14:	//taller
						node->_ListObjects.push_back(new Pipe(objectID, x, y, tag));
						break;

					//case brick with item
					case 17:	//brown brick with 1up
					case 18:	//blue brick with mushroom
					case 19:	//blue brick with 1up
					case 20:	//brown brick with coin
					case 21:	//blue brick with coin
					case 22:	//brown brick with star
					case 23:	//blue brick with star
					case 34:	//invi gray block with 1 coin
						node->_ListObjects.push_back(new ItemBrick(objectID, x, y, tag));
						break;

					//case question block
					case 6:	//normal question block
					case 16:	//question block with mushroom
						node->_ListObjects.push_back(new QuestionBlock(objectID, x, y));
						break;

					//case coin
					case 15: //coin
						node->_ListObjects.push_back(new Coin(x, y));
						break;

					//case Monster
					case 24:	//Goomba
						node->_ListObjects.push_back(new Goomba(objectID, x, y));
						break;
					case 25:	//Goomba
						node->_ListObjects.push_back(new Goomba(objectID, x, y));
						break;
					case 26:
						node->_ListObjects.push_back(new PiranhaPlant(objectID, x, y));
						break;
					case 27:
						node->_ListObjects.push_back(new PiranhaPlant(objectID, x, y));
						break;
					case 28:	//KoopaTroopa
						node->_ListObjects.push_back(new KoopaTroopa(objectID, x, y));
						break;
					case 29:	//---------KoopaTroopa--------Test KingGooba
						node->_ListObjects.push_back(new KoopaTroopa(objectID, x, y));
						break;
					case 30:	//KoopaTroopa
						node->_ListObjects.push_back(new KoopaTroopa(objectID, x, y));
						break;
					case 31:	//KoopaParatroopa
						node->_ListObjects.push_back(new KoopaParatroopa(objectID, x, y));
						break;
					case 35:
						node->_ListObjects.push_back(new Axe(x, y, w, h));
						break;
					case 36:	//BulletFire
						node->_ListObjects.push_back(new BulletFire(objectID, x, y));
						break;
					case 37:	//KingBowser
						node->_ListObjects.push_back(new KingBowser(objectID, x, y));
						break;
					case 40:	//bridge
						node->_ListObjects.push_back(new Bridge(x, y, w, h));
						break;
					case 43:	//MushroomRetainer
						node->_ListObjects.push_back(new MushroomRetainer(x, y));
					default:
						break;
					}
				}	//end for loop
				
				_MapQuadTree[nodeId] = node;
				//there is only one node has a parentId = 0
				if (parentId == 0)
					_RootNode = node;
				else
				{
					int nodePosition = nodeId % 10;
					switch (nodePosition)
					{
					case eNodePosition::eTopLeft:
						_MapQuadTree[parentId]->_Tl = node;
						break;
					case eNodePosition::eTopRight:
						_MapQuadTree[parentId]->_Tr = node;
						break;
					case eNodePosition::eBotLeft:
						_MapQuadTree[parentId]->_Bl = node;
						break;
					case eNodePosition::eBotRight:
						_MapQuadTree[parentId]->_Br = node;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	file.close();
}

void QuadTree::InsertObject(GameObject* object, Box objBox, int &returnNodeId)
{
	_RootNode->InsertObject(_MapQuadTree, object, objBox, returnNodeId);
}

void QuadTree::UpdateObjectsInNode(Node* node, Box activeSite)
{
	if (node == NULL)
		return;

	if (node->_Tl != NULL)
		UpdateObjectsInNode(node->_Tl, activeSite);
	if (node->_Tr != NULL)
		UpdateObjectsInNode(node->_Tr, activeSite);
	if (node->_Bl != NULL)
		UpdateObjectsInNode(node->_Bl, activeSite);
	if (node->_Br != NULL)
		UpdateObjectsInNode(node->_Br, activeSite);

	//check if node intersect with active site
	if (AABBCheck(node->GetBoundaryBox(), activeSite))
	{
		//browse objects in nodes
		for (int i = 0; i < node->_ListObjects.size(); )
		{
			//if object is in the active site
			if (AABBCheck(activeSite, node->_ListObjects[i]->GetBoundaryBox()))
			{
				//if object's tag is not destroy and is not remove
				if (node->_ListObjects[i]->GetTag() != eGameTag::eDestroyed && node->_ListObjects[i]->GetTag() != eGameTag::eRemove)
				{

					if (!AABBCheck(activeSite, node->_ListObjects[i]->GetBoundaryBox()))
					{
						node->_ListObjects[i]->Release();
						delete node->_ListObjects[i];
						node->_ListObjects[i] = NULL;
						node->_ListObjects.erase(node->_ListObjects.begin() + i);
						//delete node if it is empty
						if (node->IsEmpty())
							DeleteSubnode(node);
					}
					else
					{
						GameObject* currentObj = node->_ListObjects[i];
						//if object is dynamic and object moves out of node
						if (currentObj->IsDynamic() && !AABBCheck(node->GetBoundaryBox(), currentObj->GetBoundaryBox()))
						{
							//if object is still in active site
							//add object to a new node and remove object from current node
							if (AABBCheck(activeSite, currentObj->GetBoundaryBox()))
							{
								//add object to root node
								//then root node will add object to suitable subnode
								int returnNodeId = -1;
								_RootNode->InsertObject(_MapQuadTree, currentObj, currentObj->GetBoundaryBox(), returnNodeId);
								//comment TiengViet
								//khi chuyen tu node con(hoac node sau) sang node cha(hoac node truoc)
								//thi object khong duoc add vao _ObjectsOnScreen
								//do node cha(hoac node truoc) da duoc duyet roi
								//do do can add object vao _ObjectsOnScreen ngay tai node nay
								if (returnNodeId != -1 && returnNodeId < node->GetNodeId())
									_ObjectsOnScreen.push_back(currentObj);
								node->_ListObjects.erase(node->_ListObjects.begin() + i);
								//delete node if it is empty
								if (node->IsEmpty())
									DeleteSubnode(node);
							}
							//object moves out of node and out of active site
							//remove object
							else
							{
								node->_ListObjects[i]->Release();
								delete node->_ListObjects[i];
								node->_ListObjects[i] = NULL;
								node->_ListObjects.erase(node->_ListObjects.begin() + i);
								//delete node if it is empty
								if (node->IsEmpty())
									DeleteSubnode(node);
							}
						}
						//if object is static or object is still in node
						else
						{
							_ObjectsOnScreen.push_back(currentObj);
							i++;
						}
					}
				}
				//if object's tag is remove, remove object from quadtree
				else if (node->_ListObjects[i]->GetTag() == eGameTag::eRemove)
				{
					node->_ListObjects.erase(node->_ListObjects.begin() + i);
					//delete node if it is empty
					if (node->IsEmpty())
						DeleteSubnode(node);
				}
				//if object's tag is destroy, destroy object
				else 
				{
					//remove object if it's tag is destroyed
					node->_ListObjects[i]->Release();
					delete node->_ListObjects[i];
					node->_ListObjects[i] = NULL;
					node->_ListObjects.erase(node->_ListObjects.begin() + i);
					//delete node if it is empty
					if (node->IsEmpty())
						DeleteSubnode(node);
				}
			
			}
			//if object is not in the activesite
			else
			{
				//destroy objects in the left of the active site
				if (node->_ListObjects[i]->GetBoundaryBox().fX < activeSite.fX && node->_ListObjects[i]->GetTag() != eGameTag::eRemove)
				{
					node->_ListObjects[i]->Release();
					delete node->_ListObjects[i];
					node->_ListObjects[i] = NULL;
					node->_ListObjects.erase(node->_ListObjects.begin() + i);
					//delete node if it is empty
					if (node->IsEmpty())
						DeleteSubnode(node);
				}
				//increase index
				else
					i++;
			}
		}
	}
}

void QuadTree::UpdateObjectsOnScreen()
{
	if (_ObjectsOnScreen.size() > 0)
		_ObjectsOnScreen.clear();
	Box activeSite = Camera::GetInstance()->GetActiveSite();
	UpdateObjectsInNode(_RootNode, activeSite);

	//Stop update object if pause object is call
	if(!GameStatistics::GetInstance()->IsPauseObject())
	{
		for (std::vector<GameObject*>::iterator itr = _ObjectsOnScreen.begin(); itr != _ObjectsOnScreen.end(); itr++)
		{
			(*itr)->Update();
		}
	}
}

std::vector<GameObject*> QuadTree::GetObjectsOnScreen() const
{
	return _ObjectsOnScreen;
}

void QuadTree::DeleteSubnode(Node* node)
{
	if (node != NULL)
	{
		DeleteNode(node->_Tl);
		DeleteNode(node->_Tr);
		DeleteNode(node->_Bl);
		DeleteNode(node->_Br);
	}
}

void QuadTree::DeleteNode(Node* node)
{
	if (node != NULL)
	{
		DeleteNode(node->_Tl);
		DeleteNode(node->_Tr);
		DeleteNode(node->_Bl);
		DeleteNode(node->_Br);

		int id = node->GetNodeId();
		node->Release();
		delete node;
		node = NULL;
		if (_MapQuadTree.find(id) != _MapQuadTree.end())
			_MapQuadTree.erase(id);
	}
}

void QuadTree::Release()
{
	_ObjectsOnScreen.clear();
	DeleteNode(_RootNode);
	_MapQuadTree.clear();
}

QuadTree::~QuadTree()
{
}
