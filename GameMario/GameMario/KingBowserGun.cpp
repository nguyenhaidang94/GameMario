#include "KingBowserGun.h"

KingBowserGun *KingBowserGun::Instance = NULL;

KingBowserGun::KingBowserGun()
{
	PoolBullet.push_back(new BulletFire());
	PoolBullet.push_back(new BulletFire());
}


KingBowserGun::~KingBowserGun()
{

}

KingBowserGun::KingBowserGun(int ObjectTypeID, int PossitionX, int PossitionY)
{

}

KingBowserGun *KingBowserGun::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new KingBowserGun();
	}

	return Instance;
}

void KingBowserGun::GunShoot(D3DXVECTOR2 PositionBullet, bool IsLeft, D3DXVECTOR2 PositionKing, int BulletType)
{
	if (PoolBullet.size() != 0)
	{
		ListBullet.push_back(PoolBullet[PoolBullet.size() - 1]);	//thêm bullet Pool vào list
		PoolBullet.pop_back();										//do đã thêm vào nên xóa đi
		ListBullet[ListBullet.size() - 1]->SetBullet(PositionBullet, IsLeft, PositionKing, BulletType);
		ListBullet[ListBullet.size() - 1]->SetTag(eEmpty);
		GameStatistics::GetInstance()->AddObjectToScene(ListBullet[ListBullet.size() - 1]);
	}

	//Update live
	Update();
}

//Update object
void KingBowserGun::Update()
{
	if (ListBullet.size() != 0)
	{
		for (int i = 0; i <= ListBullet.size() - 1; i++)
		{
			int a = ListBullet[i]->GetPosition().x;
			int b = Camera::GetInstance()->GetViewPort().x;
			int c = Camera::GetInstance()->GetViewPort().x + SCREEN_WIDTH + BUFFER_FOR_SCREEN;
			if (ListBullet[i]->GetPosition().x <= Camera::GetInstance()->GetViewPort().x + 10 ||
				 ListBullet[i]->GetPosition().x >= Camera::GetInstance()->GetViewPort().x + SCREEN_WIDTH + BUFFER_FOR_SCREEN - 10)
			{
				ListBullet[i]->SetTag(eRemove);
				PoolBullet.push_back(ListBullet[i]);

				if (ListBullet.size() != 0)
				{
					ListBullet.erase(ListBullet.begin() + i);
					i--;
				}

				if (ListBullet.size() == 0) 
					break;
			}
		}
	}
}

//Draw object to screen
void KingBowserGun::Render()
{
	if (ListBullet.size() != 0)
	{
		for (int i = 0; i <= ListBullet.size() - 1; i++)
		{
			ListBullet[i]->Render();
		}
	}
}

//Removes a gameobject, component or asset.
void KingBowserGun::Release()
{
	if (ListBullet.size() != 0)
	{
		for (int i = 0; i <= ListBullet.size() - 1; i++)
		{
			ListBullet[i]->SetTag(eRemove);
			PoolBullet.push_back(ListBullet[i]);

			if (ListBullet.size() != 0)
			{
				ListBullet.erase(ListBullet.begin() + i);
				i--;
			}

			if (ListBullet.size() == 0)
				break;
		}
	}
}

//Handling object when colision happened
void KingBowserGun::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{

}

