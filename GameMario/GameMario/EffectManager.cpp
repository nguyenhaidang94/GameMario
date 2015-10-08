#include "EffectManager.h"

EffectManager *EffectManager::Instance = NULL;

EffectManager::EffectManager(void)
{
}


EffectManager::~EffectManager(void)
{
}

EffectManager *EffectManager::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new EffectManager();
	}
	return Instance;
}

void EffectManager::ShowEffect(D3DXVECTOR2 position ,eEffectID effectID, int tag)
{
	switch (effectID)
	{
	case eBrickBreak:
		if(tag >= 0 && tag <= 1)	//this effect currently only have 2 effect at 0 and 1
		{
			_ListEffect.push_back(new BrickBreakEffect(position, tag));
		}
		break;
	default:
		break;
	}
}

void EffectManager::Update()
{
	for(int i = 0; i < _ListEffect.size(); i++)
	{
		if(_ListEffect[i]->CheckAlive())
		{
			_ListEffect[i]->Update();
		}
		else
		{
			_ListEffect.erase(_ListEffect.begin() + i);	//delete current effect if it died
		}
	}
}

void EffectManager::Render()
{
	for(int i = 0; i < _ListEffect.size(); i++)
	{
		_ListEffect[i]->Render();
	}
}

void EffectManager::Release()
{
	for(int i = 0; i < _ListEffect.size(); i++)
	{
		_ListEffect[i]->Release();
	}
}