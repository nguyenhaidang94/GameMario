#include "FloatingTextEffect.h"

#define DEFAULT_VELOCITY_Y -5	//negative value because this use top-left positon
#define DISAPPEAR_RANGE 64

FloatingTextEffect::FloatingTextEffect(void)
{
}

FloatingTextEffect::FloatingTextEffect(D3DXVECTOR2 position, string score)
{
	_ScorePosition = WorldPostionToFixedPostion(position);
	_BeginingY = _ScorePosition.y;
	_Score = score;
	_ScoresVelocity.y = DEFAULT_VELOCITY_Y;
	_IsAlive = true;
}

FloatingTextEffect::~FloatingTextEffect(void)
{
}

D3DXVECTOR2 FloatingTextEffect::WorldPostionToFixedPostion(D3DXVECTOR2 position)
{
	return D3DXVECTOR2(position.x - Camera::GetInstance()->GetViewPort().x, Camera::GetInstance()->GetViewPort().y - position.y);
}

void FloatingTextEffect::Update()
{
	if(_IsAlive)
	{
		if(_ScorePosition.y < _BeginingY - DISAPPEAR_RANGE)
		{
			_IsAlive = false;
		}
		_ScorePosition.y += _ScoresVelocity.y;
	}
}

void FloatingTextEffect::Render()
{
	if(_IsAlive)
	{
		TextManager::GetInstance()->FixedRender(_Score, _ScorePosition.x, _ScorePosition.y);
	}
}

void FloatingTextEffect::Release()
{
	
}