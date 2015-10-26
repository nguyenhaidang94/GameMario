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
		break;
	case e1_4:
		break;
	case eUnderground1_1:
		fileName = "u1_1_quadtree";
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
						node->_ListObjects.push_back(new Ground(x, y, w));
						break;

					//Case brick
					case 2:	//brown normal
					case 3:	//blue normal
						node->_ListObjects.push_back(new Brick(objectID, x, y));
						break;
					//Case hard block
					case 4:
						node->_ListObjects.push_back(new HardBlock(objectID, x, y));
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

void QuadTree::InsertObject(GameObject* object, Box objBox)
{
	_RootNode->InsertObject(_MapQuadTree, object, objBox);
}

void QuadTree::RetrieveObjectsInNode(Node* node, Box sightBox)
{
	if (node == NULL)
		return;

	if (node->_Tl != NULL)
		RetrieveObjectsInNode(node->_Tl, sightBox);
	if (node->_Tr != NULL)
		RetrieveObjectsInNode(node->_Tr, sightBox);
	if (node->_Bl != NULL)
		RetrieveObjectsInNode(node->_Bl, sightBox);
	if (node->_Br != NULL)
		RetrieveObjectsInNode(node->_Br, sightBox);

	if (AABBCheck(node->GetBoundaryBox(), sightBox))
	{
		for (int i = 0; i < node->_ListObjects.size(); )
		{
			if (node->_ListObjects[i]->GetTag() != eGameTag::eDestroyed)
			{
				node->_ListObjects[i]->Update();
				//if object is dynamic and object moves out of node
				if (node->_ListObjects[i]->IsDynamic() && !AABBCheck(node->GetBoundaryBox(), node->_ListObjects[i]->GetBoundaryBox()))
				{
					//this if is used for a special situation, but actually it doesn't have to used
					//if (node != _RootNode)
					{
						//add object to root node
						//then root node will add object to suitable subnode
						_RootNode->InsertObject(_MapQuadTree, node->_ListObjects[i], node->_ListObjects[i]->GetBoundaryBox());
						node->_ListObjects.erase(node->_ListObjects.begin() + i);
						//delete node if it is empty
						if (node->IsEmpty())
							DeleteSubnode(node);
					}
				}
				else
				{
					//check if object intersects with sightBox
					if (AABBCheck(sightBox, node->_ListObjects[i]->GetBoundaryBox()))
						_ObjectsOnScreen.push_back(node->_ListObjects[i]);
					i++;
				}
			}
			else
			{
				//remomve object if it's destroyed
				node->_ListObjects[i]->Release();
				delete node->_ListObjects[i];
				node->_ListObjects[i] = NULL;
				node->_ListObjects.erase(node->_ListObjects.begin() + i);
				//delete node if it is empty
				if (node->IsEmpty())
					DeleteSubnode(node);
			}
		}
	}
}

void QuadTree::UpdateObjectsOnScreen()
{
	if (_ObjectsOnScreen.size() > 0)
		_ObjectsOnScreen.clear();
	Box cameraBox = Camera::GetInstance()->GetBoundaryBox();
	RetrieveObjectsInNode(_RootNode, cameraBox);
}

std::vector<GameObject*> QuadTree::GetObjectsOnScreen()
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
