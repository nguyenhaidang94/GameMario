#include "QuadTree.h"

QuadTree* QuadTree::_Instance = NULL;

QuadTree::QuadTree()
{
	_RootNode = NULL;
}

QuadTree* QuadTree::GetInstance()
{
	if (_Instance == NULL)
		_Instance = new QuadTree();
	return _Instance;
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
						node->_ListObjects.push_back(new Ground(x, y, atoi(tag.c_str())));
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
					case 10:		//medium
					case 11:		//big
					case 12:		//horizontal
						node->_ListObjects.push_back(new Pipe(objectID, x, y, tag));
						break;

						//case brick with item
					case 18:	//brick with 1up
					case 20:	//brick with coin
					case 22:	//brick with star
						node->_ListObjects.push_back(new ItemBrick(objectID, x, y, tag));
						break;

						//case question block
					case 6:	//normal question block
					case 16:	//question block with mushroom
						node->_ListObjects.push_back(new QuestionBlock(objectID, x, y));
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
					case (int)eNodePosition::eTopLeft:
						_MapQuadTree[parentId]->_Tl = node;
						break;
					case (int)eNodePosition::eTopRight:
						_MapQuadTree[parentId]->_Tr = node;
						break;
					case (int)eNodePosition::eBotLeft:
						_MapQuadTree[parentId]->_Bl = node;
						break;
					case (int)eNodePosition::eBotRight:
						_MapQuadTree[parentId]->_Br = node;
						break;
					default:
						break;
					}
				}
			}
		}
	}

}

void QuadTree::RetrieveObjectsInNode(Node* node, Box sightBox)
{
	if (AABBCheck(node->GetBoundaryBox(), sightBox))
	{
		if (node->_ListObjects.size() > 0)
		{
			for (int i = 0; i < node->_ListObjects.size(); i++)
				_ObjectsOnScreen.push_back(node->_ListObjects[i]);
		}
		if (node->_Tl != NULL)
			RetrieveObjectsInNode(node->_Tl, sightBox);
		if (node->_Tr != NULL)
			RetrieveObjectsInNode(node->_Tr, sightBox);
		if (node->_Bl != NULL)
			RetrieveObjectsInNode(node->_Bl, sightBox);
		if (node->_Br != NULL)
			RetrieveObjectsInNode(node->_Br, sightBox);
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

void QuadTree::Clear(Node* node)
{
	if (node != NULL)
	{
		Clear(node->_Tl);
		delete node->_Tl;
		Clear(node->_Tr);
		delete node->_Tr;
		Clear(node->_Bl);
		delete node->_Bl;
		Clear(node->_Br);
		delete node->_Br;

		node->Release();
		delete node;
	}
}

void QuadTree::Release()
{
	_ObjectsOnScreen.clear();
	_MapQuadTree.clear();
	Clear(_RootNode);
}

QuadTree::~QuadTree()
{
}
