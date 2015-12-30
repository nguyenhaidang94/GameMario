#include "Gun.h"

Gun *Gun::Instance = NULL;

Gun::Gun(void)
{
	_IsShoot = false;
	PoolBullet.push_back(new Bullet());
	PoolBullet.push_back(new Bullet());
	_Camera = Camera::GetInstance();
}

Gun *Gun::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new Gun();
	}
	return Instance;
}

bool Gun::GetStatus()
{
	return _IsShoot;
}

void Gun::Shoot(D3DXVECTOR2 MarioPosition, bool IsRight)
{
	if(Keyboard::GetInstance()->IsKeyPress(DIK_J))
	{
		if(PoolBullet.size()!=0)
		{
			ListBullet.push_back(PoolBullet[PoolBullet.size()-1]);
			PoolBullet.pop_back();
			
			if(IsRight==true) 
			{
				ListBullet[ListBullet.size()-1]->SetPosition(D3DXVECTOR2(MarioPosition.x+16,MarioPosition.y+32));
				ListBullet[ListBullet.size()-1]->SetRight(IsRight);
			}
			else 
			{
				ListBullet[ListBullet.size()-1]->SetPosition(D3DXVECTOR2(MarioPosition.x-16,MarioPosition.y+32));
				ListBullet[ListBullet.size()-1]->SetRight(IsRight);
			}

			ListBullet[ListBullet.size()-1]->SetTag(eEmpty);	

			GameStatistics::GetInstance()->AddObjectToScene(ListBullet[ListBullet.size()-1]);
		
		}
	}

	Update();
}
bool Gun::SetStatus()
{
	for(int i=0;i<=ListBullet.size()-1;i++)
	{
		if(ListBullet[i]->GetTime() >= 100) 
		{
			return _IsShoot = false;
		}
	}

	return _IsShoot = true;
}
void Gun::Release()
{
}

void Gun::Update()
{

 if(ListBullet.size() !=0)
 {
	for(int i=0;i<=ListBullet.size()-1;i++)
	{
		if(ListBullet[i]->GetTime() < 100 && ListBullet[i]->GetPosition().x < _Camera->GetBoundaryBox().fX+ _Camera->GetBoundaryBox().fWidth - 5
			&& ListBullet[i]->GetPosition().y > 20 && ListBullet[i]->GetPosition().x > _Camera->GetBoundaryBox().fX  + 5) 
		{
			ListBullet[i]->Update();
		}
		else
		{
			ListBullet[i]->SetIsEF(true);
			ListBullet[i]->SetTimeAlive(0);
			ListBullet[i]->SetCollision(false);
			ListBullet[i]->SetTime(0);
			ListBullet[i]->SetTag(eRemove);
			PoolBullet.push_back(ListBullet[i]);

			if(ListBullet.size()!=0) 
			{
				ListBullet.erase(ListBullet.begin() + i);
				i--;
			}

			if(ListBullet.size() == 0) break;
		}
	}
 }

}

void Gun::Render()
{
	if(ListBullet.size()!=0)
	{
		for(int i=0;i<=ListBullet.size()-1;i++)
		{
			ListBullet[i]->Render();
		}
	}
}

void Gun::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
}
Gun::~Gun(void)
{
}
