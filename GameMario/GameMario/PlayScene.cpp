#include "PlayScene.h"

PlayScene *PlayScene::Instance = NULL;

PlayScene::PlayScene(void)
{
	
}

PlayScene::~PlayScene(void)
{
}

PlayScene *PlayScene::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new PlayScene();
	}
	return Instance;
}

void PlayScene::Initialize()
{
	_Background = new Background();
	_Mario = new Mario();
	_MapID = eWorldID::e1_1;
}

void PlayScene::Load()
{
	LoadMap(GameStatistics::GetInstance()->GetWorldID());
	GameStatistics::GetInstance()->ResetTime();
}

void PlayScene::LoadMap(eWorldID mapID)
{
	this->Release();
	_MapID = mapID;
	//Reset some object
	_Background->ReadMapData(_MapID);
	_Mario->SetPosition(D3DXVECTOR2(32,256));
	//Read object data in map
	//ReadMapData();
	QuadTree::GetInstance()->BuildQuadTree(_MapID);
}

void PlayScene::Update()
{
	_Mario->Update();
	//for (int i = 0; i < _ListObject.size(); i++)
	//{
	//	if (_ListObject[i]->GetTag() != eGameTag::eDestroyed)
	//	{
	//		_ListObject[i]->Update();
	//	}
	//	else
	//	{
	//		//remomve object if it's destroyed
	//		delete _ListObject[i];
	//		_ListObject.erase(_ListObject.begin() + i);
	//	}
	//}

	QuadTree::GetInstance()->UpdateObjectsOnScreen();
	std::vector<GameObject*> listObjects = QuadTree::GetInstance()->GetObjectsOnScreen();
	//for (int i = 0; i < listObjects.size(); i++)
	//{
	//	if (listObjects[i]->GetTag() != eGameTag::eDestroyed)
	//	{
	//		listObjects[i]->Update();
	//	}
	//	else
	//	{
	//		//remomve object if it's destroyed
	//		delete listObjects[i];
	//		listObjects.erase(_ListObject.begin() + i);
	//	}
	//}

	//Handling colison
	HandlingCollision();

	//Update camera
	Camera::GetInstance()->Update(_Mario->GetPosition());
	
	//Test switch map
	//if(_Mario->GetPosition().x >= Camera::GetInstance()->GetWorldSize().x)
	//{
	//	GameStatistics::GetInstance()->ChangeWorld(eWorldID::e1_2);
	//	SceneManager::GetInstance()->SwitchScene(eSceneID::eStartMap);
	//}
}

void PlayScene::Render()
{
	_Background->Render();
	_Mario->Render();
	/*for (int i = 0; i < _ListObject.size(); i++)
	{
		_ListObject[i]->Render();
	}*/
	vector<GameObject*> listObj = QuadTree::GetInstance()->GetObjectsOnScreen();
	for (int i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Render();
	}
}

void PlayScene::Release()
{
	_Background->Release();
	QuadTree::GetInstance()->Release();
}

void PlayScene::HandlingCollision()
{
	//vector<GameObject*> objectOnScreen = GetListObjectOnScreen();
	vector<GameObject*> objectOnScreen = QuadTree::GetInstance()->GetObjectsOnScreen();
	float moveX, moveY;

	//--Variable to handle collide with multiple brick--
	int indexClosestBrickCollide = -1;	//mario only collide on top with 1 brick at the time, this store the closest one

	//--Handle collision with all object on screen
	for (int i = 0; i < objectOnScreen.size(); i++)
	{
		//check colision with mario...
		eCollisionDirection direction = CheckCollision(_Mario, objectOnScreen[i], moveX, moveY);
		if(direction != eCollisionDirection::eNone)
		{
			//if collide with brick on top, store and handle later
			if (objectOnScreen[i]->GetObjectTypeID() == eObjectTypeID::eBrick && direction == eCollisionDirection::eBottom)
			{
				//if 1st brick
				if(indexClosestBrickCollide == -1)
				{
					indexClosestBrickCollide = i;
				}
				else
				{
					//check if it closer than the closest
					if (abs(_Mario->GetPosition().x - objectOnScreen[i]->GetPosition().x) <
						abs(_Mario->GetPosition().x - objectOnScreen[indexClosestBrickCollide]->GetPosition().x))
					{
						indexClosestBrickCollide = i;
					}
				}
			}
			else	//send collision
			{
				_Mario->OnCollision(objectOnScreen[i], Unility::GetOppositeDirection(direction));
				objectOnScreen[i]->OnCollision(_Mario, direction);
			}
		}

		//and for other, FIX LATER
		for (int j = i + 1; j < objectOnScreen.size(); j++)
		{
			
			eCollisionDirection direction = CheckCollision(objectOnScreen[i], objectOnScreen[j], moveX, moveY);
			if(direction != eCollisionDirection::eNone)
			{
				objectOnScreen[i]->OnCollision(objectOnScreen[j], Unility::GetOppositeDirection(direction));
				objectOnScreen[j]->OnCollision(objectOnScreen[i], direction);
			}
		}
	}
	//Handle collide with brick if have any
	if(indexClosestBrickCollide != -1)
	{
		_Mario->OnCollision(objectOnScreen[indexClosestBrickCollide], Unility::GetOppositeDirection(eCollisionDirection::eBottom));
		objectOnScreen[indexClosestBrickCollide]->OnCollision(_Mario, eCollisionDirection::eBottom);
	}
}

//-------------------------------------------------------------
//check collision of an dynamic object with another object
//return CollisionDirection of 2nd object
//-------------------------------------------------------------
eCollisionDirection PlayScene::CheckCollision(GameObject *dynamicObj, GameObject *unknownObj, float &moveX, float &moveY)
{
	float normalX, normalY;
	Box dynamicBox = dynamicObj->GetBoundaryBox();
	Box unknownBox = unknownObj->GetBoundaryBox();

	//neu chua va cham
	if (AABB(dynamicBox, unknownBox, moveX, moveY) == false)
	{
		//neu unknownObj co van toc thi tru van toc 2 vat
		if (unknownBox.fVx != 0.0f || unknownBox.fVy != 0.0f)
		{
			dynamicBox.fVx -= unknownBox.fVx;
			dynamicBox.fVy -= unknownBox.fVy;
			unknownBox.fVx = 0.0f;
			unknownBox.fVy = 0.0f;
		}

		//lay box o fram ke tiep
		Box broadphasebox = getSweptBroadphaseBox(dynamicBox);
		//neu o frame ke tiep vat se va cham
		if (AABB(broadphasebox, unknownBox, moveX, moveY) == true)
		{
			//su dung thuat toan sweptAABB de xac dinh va cham
			float collisiontime = sweptAABB(dynamicBox, unknownBox, normalX, normalY);
			//truong hop co xay ra va cham
			if (collisiontime > 0.0f && collisiontime < 1.0f)
			{
				//normalY != 0.0f va moveY != 0 tuc va cham theo phuong doc
				if (normalY != 0.0f && moveY != 0)
				{
					//va cham top
					if (normalY == 1.0f)
					{
						//MessageBox(_hWnd, L"top", L"collision", MB_OK);
						return eCollisionDirection::eTop;
					}
					//va cham bot
					else if (normalY == -1.0f)
					{
						//MessageBox(_hWnd, L"bottom", L"collision", MB_OK);
						return eCollisionDirection::eBottom;
					}
				}
				//normalX != 0.0f va moveX != 0 tuc va cham theo phuong ngang
				else if (normalX != 0.0f && moveX != 0.0f)
				{
					//va cham right
					if (normalX == 1.0f)
					{
						//MessageBox(_hWnd, L"right", L"collision", MB_OK);
						return eCollisionDirection::eRight;
					}
					//va cham left
					else if (normalX == -1.0f)
					{
						//MessageBox(_hWnd, L"left", L"collision", MB_OK);
						return eCollisionDirection::eLeft;
					}
				}
			}
		}
	}
	//neu da va cham
	else
	{
		//va cham theo phuong doc
		if (moveY != 0)
		{
			//top
			if (moveY > 0.0f)
			{
				//MessageBox(_hWnd, L"top", L"collision", MB_OK);
				return eCollisionDirection::eTop;
			}
			//bot
			else
			{
				//MessageBox(_hWnd, L"bottom", L"collision", MB_OK);
				return eCollisionDirection::eBottom;
			}
		}
		//va cham theo phuong ngang
		else if (moveX != 0)
		{
			//left
			if (moveX < 0.0f)
			{
				//MessageBox(_hWnd, L"left", L"collision", MB_OK);
				return eCollisionDirection::eLeft;
			}
			//right
			else
			{
				//MessageBox(_hWnd, L"right", L"collision", MB_OK);
				return eCollisionDirection::eRight;
			}
		}
		//moveX == 0 va move Y == 0 tuc 2 vat dang tiep xuc
		else
		{
			//truong hop goc cham goc thi khong xac dinh duoc huong va cham
			if (dynamicBox.fY - dynamicBox.fHeight == unknownBox.fY && dynamicBox.fX + dynamicBox.fWidth == unknownBox.fX
				|| dynamicBox.fY - dynamicBox.fHeight == unknownBox.fY && dynamicBox.fX == unknownBox.fX + unknownBox.fWidth)
				return eCollisionDirection::eNone;

			//tiep xuc voi mat tren cua vat unknown
			if (dynamicBox.fY - dynamicBox.fHeight == unknownBox.fY)
			{
				//MessageBox(_hWnd, L"top", L"collision", MB_OK);
				return eCollisionDirection::eTop;
			}
			//tiep xuc o mat duoi cua vat unknown
			else if (dynamicBox.fY == unknownBox.fY - unknownBox.fHeight)
			{
				//MessageBox(_hWnd, L"bottom", L"collision", MB_OK);
				return eCollisionDirection::eBottom;
			}
			//tiep xuc o mat trai cua vat unknown
			else if (dynamicBox.fX + dynamicBox.fWidth == unknownBox.fX)
			{
				//MessageBox(_hWnd, L"left", L"collision", MB_OK);
				return eCollisionDirection::eLeft;
			}
			//tiep xuc o mat phai cua vat unknown
			else if (dynamicBox.fX == unknownBox.fX + unknownBox.fWidth)
			{
				//MessageBox(_hWnd, L"right", L"collision", MB_OK);
				return eCollisionDirection::eRight;
			}
		}
	}

	return eCollisionDirection::eNone;
}
