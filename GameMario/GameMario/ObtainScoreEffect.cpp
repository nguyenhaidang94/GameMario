#include "ObtainScoreEffect.h"

#define DEFAULT_VELOCITY_Y -5	//negative value because this use top-left positon
#define DISAPPEAR_RANGE 64

ObtainScoreEffect::ObtainScoreEffect(void)
{
}

ObtainScoreEffect::ObtainScoreEffect(D3DXVECTOR2 position, int score)
{
	_ScorePosition = WorldPostionToFixedPostion(position);
	_BeginingY = _ScorePosition.y;
	_Score = score;
	_ScoresVelocity.y = DEFAULT_VELOCITY_Y;
	_IsAlive = true;
}

ObtainScoreEffect::~ObtainScoreEffect(void)
{
}

D3DXVECTOR2 ObtainScoreEffect::WorldPostionToFixedPostion(D3DXVECTOR2 position)
{
	//x axis hardcode minus 30 to center text
	return D3DXVECTOR2(position.x - Camera::GetInstance()->GetViewPort().x - 30, Camera::GetInstance()->GetViewPort().y - position.y);
}

void ObtainScoreEffect::Update()
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

void ObtainScoreEffect::Render()
{
	if(_IsAlive)
	{
		TextManager::GetInstance()->FixedRender(to_string(_Score), _ScorePosition.x, _ScorePosition.y);
	}
}

void ObtainScoreEffect::Release()
{
	
}