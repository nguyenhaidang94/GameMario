#include "PlayMap.h"

PlayMap::PlayMap(void)
{
	_Background = new Background();
	_QuadTree = new QuadTree();
	_Mario = Mario::GetInstance();
}

PlayMap::PlayMap(eWorldID worldID)
{
	_Background = new Background();
	_QuadTree = new QuadTree();
	_Mario = Mario::GetInstance();

	_WorldID = worldID;
	_Background->ReadMapData(_WorldID);

	//Read map file and built quadtree
	_QuadTree->BuildQuadTree(_WorldID);
}

PlayMap::~PlayMap(void)
{
}

void PlayMap::Update()
{
	//Handling colison
	HandlingCollision();

	//update objects
	_Mario->Update();
	_QuadTree->UpdateObjectsOnScreen();

	//Update camera
	Camera::GetInstance()->Update(_Mario->GetPosition());
}

void PlayMap::Render()
{
	_Background->Render();
	vector<GameObject*> listObj = _QuadTree->GetObjectsOnScreen();
	if(_Mario->GetFlagAutoAnimationRight()==false)
	{
		for (int i = 0; i < listObj.size(); i++)
		{
			listObj[i]->Render();
		}
		_Mario->Render();
	}
	else
	{
		_Mario->Render();
		for (int i = 0; i < listObj.size(); i++)
		{
			listObj[i]->Render();
		}
	}
}

void PlayMap::Release()
{
	_Background->Release();
	_QuadTree->Release();
}

void PlayMap::Load()
{
	Camera::GetInstance()->SetWorldSize(_Background->GetWorldSize());		//set camera boundary
}

void PlayMap::Reload()
{
	Camera::GetInstance()->SetWorldSize(_Background->GetWorldSize());		//set camera boundary
	_QuadTree->Release();
	_QuadTree->BuildQuadTree(_WorldID);
}

void PlayMap::AddObjectToMap(GameObject *object)
{
	int returnNodeId;
	_QuadTree->InsertObject(object, object->GetBoundaryBox(), returnNodeId);
}

void PlayMap::HandlingCollision()
{
	vector<GameObject*> objectOnScreen = _QuadTree->GetObjectsOnScreen();

	//remove all object have ignore collision tag
	for (int i = objectOnScreen.size() - 1; i >= 0; i--)
	{
		if(objectOnScreen[i]->GetTag() == eGameTag::eIgnoreCollision)
		{
			objectOnScreen.erase(objectOnScreen.begin() + i);
		}
	}

	//--Variable to handle collide with multiple brick--
	int indexClosestBrickCollide = -1;	//mario only collide on top with 1 brick at the time, this store the closest one

	float offsetX;
	float offsetY;

	//used when mario's head collides with brick's bottom point
	float mario_brick_offsetX;
	float mario_brick_offsetY;
	//--Handle collision with all object on screen
	for (int i = 0; i < objectOnScreen.size(); i++)
	{
		//check colision with mario if it's not has eIgnoreCollision Tag
		if(_Mario->GetTag() != eGameTag::eIgnoreCollision)
		{
			eCollisionDirection direction = CheckCollision(_Mario, objectOnScreen[i], offsetX, offsetY);
			if(direction != eCollisionDirection::eNone && _Mario->GetTag()!= eGameTag::eMarioIsDead)
			{
				//if collide with brick on top, store and handle later
				if (objectOnScreen[i]->GetObjectTypeID() == eObjectTypeID::eBrick && direction == eCollisionDirection::eBottom)
				{
					//if 1st brick
					if(indexClosestBrickCollide == -1)
					{
						indexClosestBrickCollide = i;
						mario_brick_offsetX = offsetX;
						mario_brick_offsetY = offsetY;
					}
					else
					{
						//check if it closer than the closest
						if (abs(_Mario->GetPosition().x - objectOnScreen[i]->GetPosition().x)
							< abs(_Mario->GetPosition().x - objectOnScreen[indexClosestBrickCollide]->GetPosition().x))
						{
							indexClosestBrickCollide = i;
							mario_brick_offsetX = offsetX;
							mario_brick_offsetY = offsetY;
						}
					}
				}
				else	//send collision
				{
					_Mario->OnCollision(objectOnScreen[i], Unility::GetOppositeDirection(direction));
					objectOnScreen[i]->OnCollision(_Mario, direction);
				}
			}
		}

		//and for other, FIX LATER
		for (int j = i + 1; j < objectOnScreen.size(); j++)
		{
			
			eCollisionDirection direction = CheckCollision(objectOnScreen[i], objectOnScreen[j], offsetX, offsetY);
			if(direction != eCollisionDirection::eNone)
			{
				objectOnScreen[i]->OnCollision(objectOnScreen[j], Unility::GetOppositeDirection(direction));
				objectOnScreen[j]->OnCollision(objectOnScreen[i], direction);
			}
		}
	}
	//Handle collide with brick if have any
	//offset must be greater than a constant
	if (indexClosestBrickCollide != -1 && mario_brick_offsetX > 8)
	{
		_Mario->OnCollision(objectOnScreen[indexClosestBrickCollide], Unility::GetOppositeDirection(eCollisionDirection::eBottom));
		objectOnScreen[indexClosestBrickCollide]->OnCollision(_Mario, eCollisionDirection::eBottom);
	}
}

//-------------------------------------------------------------
//check collision of an dynamic object with another object
//return CollisionDirection of 2nd object
//-------------------------------------------------------------
eCollisionDirection PlayMap::CheckCollision(GameObject *targetObj, GameObject *unknownObj, float &offsetX, float &offsetY)
{
	float normalX, normalY;
	float moveX, moveY;
	Box dynamicBox = targetObj->GetBoundaryBox();
	Box unknownBox = unknownObj->GetBoundaryBox();

	//neu chua va cham
	if (AABB(dynamicBox, unknownBox, moveX, moveY, offsetX, offsetY) == false)
	{
		if (targetObj->IsDynamic())
		{
			DynamicGameObject* dynamicObj = (DynamicGameObject*)targetObj;
			//neu unknownObj co van toc thi tru van toc 2 vat
			if (unknownObj->IsDynamic())
			{
				dynamicBox.fVx -= unknownBox.fVx;
				dynamicBox.fVy -= unknownBox.fVy;
				unknownBox.fVx = 0.0f;
				unknownBox.fVy = 0.0f;
			}

			//lay vung khong gian cua vat 1
			Box broadphasebox = getSweptBroadphaseBox(dynamicBox);
			//neu vat 2 nam trong vung khong gian cua vat 1
			if (AABB(broadphasebox, unknownBox, moveX, moveY, offsetX, offsetY) == true)
			{
				//su dung thuat toan sweptAABB de xac dinh va cham
				float collisiontime = sweptAABB(dynamicBox, unknownBox, normalX, normalY);
				//truong hop co xay ra va cham
				if (collisiontime > 0.0f && collisiontime < 1.0f)
				{
					//normalY != 0.0f va moveY != 0 tuc va cham theo phuong doc
					if (normalY != 0.0f && moveY != 0)
					{
						//va cham top, truong hop moveY <= 0 thi khong tinh va cham
						if (normalY == 1.0f && moveY > 0)
						{
							return eCollisionDirection::eTop;
						}
						//va cham bot, truong hop moveY >= 0 thi khong tinh va cham
						else if (normalY == -1.0f && moveY < 0)
						{
							return eCollisionDirection::eBottom;
						}
					}
					//normalX != 0.0f va moveX != 0 tuc va cham theo phuong ngang
					else if (normalX != 0.0f && moveX != 0.0f)
					{
						//va cham right, truong hop moveX >= 0 thi khong tinh va cham
						if (normalX == 1.0f && moveX < 0)
						{
							return eCollisionDirection::eRight;
						}
						//va cham left, truong hop moveX <= 0 thi khong tinh va cham
						else if (normalX == -1.0f && moveX > 0)
						{
							return eCollisionDirection::eLeft;
						}
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
				return eCollisionDirection::eTop;
			}
			//bot
			else
			{
				return eCollisionDirection::eBottom;
			}
		}
		//va cham theo phuong ngang
		else if (moveX != 0)
		{
			//left
			if (moveX < 0.0f)
			{
				return eCollisionDirection::eLeft;
			}
			//right
			else
			{
				return eCollisionDirection::eRight;
			}
		}
		//moveX == 0 va move Y == 0 tuc 2 vat dang tiep xuc
		else
		{
			//truong hop goc cham goc thi khong xac dinh duoc huong va cham
					//top left dynamicbox collide with bot right unknownbox
			if ((dynamicBox.fY == unknownBox.fY - unknownBox.fHeight && dynamicBox.fX == unknownBox.fX + unknownBox.fWidth)
					//top right dynamicbox collide with bot left unknownbox
				|| (dynamicBox.fY == unknownBox.fY - unknownBox.fHeight && dynamicBox.fX + dynamicBox.fWidth == unknownBox.fX)
					//bot right dynamicbox collide with top left unknowbox
				|| (dynamicBox.fY - dynamicBox.fHeight == unknownBox.fY && dynamicBox.fX + dynamicBox.fWidth == unknownBox.fX)
					//bot left dynamicbox collide with top right unknowbox
				|| (dynamicBox.fY - dynamicBox.fHeight == unknownBox.fY && dynamicBox.fX == unknownBox.fX + unknownBox.fWidth)
				)
				return eCollisionDirection::eNone;

			//tiep xuc voi mat tren cua vat unknown
			if (dynamicBox.fY - dynamicBox.fHeight == unknownBox.fY)
			{
				return eCollisionDirection::eTop;
			}
			//tiep xuc o mat duoi cua vat unknown
			else if (dynamicBox.fY == unknownBox.fY - unknownBox.fHeight)
			{
				return eCollisionDirection::eBottom;
			}
			//tiep xuc o mat trai cua vat unknown
			else if (dynamicBox.fX + dynamicBox.fWidth == unknownBox.fX)
			{
				return eCollisionDirection::eLeft;
			}
			//tiep xuc o mat phai cua vat unknown
			else if (dynamicBox.fX == unknownBox.fX + unknownBox.fWidth)
			{
				return eCollisionDirection::eRight;
			}
		}
	}
	return eCollisionDirection::eNone;
}