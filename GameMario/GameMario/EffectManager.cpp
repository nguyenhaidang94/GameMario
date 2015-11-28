#include "EffectManager.h"
#include "BrickBreakEffect.h"

EffectManager *EffectManager::_Instance = NULL;

EffectManager::EffectManager(void)
{
}


EffectManager::~EffectManager(void)
{
}

EffectManager *EffectManager::GetInstance()
{
	if(_Instance == NULL)
	{
		_Instance = new EffectManager();
	}
	return _Instance;
}

void EffectManager::ShowEffect(D3DXVECTOR2 position ,eEffectID effectID, int tag)
{
	switch (effectID)
	{
	case eBreakBrick:
		if(tag >= 0 && tag <= 1)	//this effect currently only have 2 effect at 0 and 1, zero is brown and 1 is blue
		{
			_ListEffect.push_back(new BrickBreakEffect(position, tag));
		}
		break;
	case eObtainCoin:
		_ListEffect.push_back(new ObtainCoinEffect(position, tag));
		break;
	case eFloatingText:
		if(tag == -2)	//-2 is tag for 1up mushroom
		{
			_ListEffect.push_back(new FloatingTextEffect(position, "1up"));
		}
		else
		{
			_ListEffect.push_back(new FloatingTextEffect(position, to_string(tag)));
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
			delete _ListEffect[i];
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