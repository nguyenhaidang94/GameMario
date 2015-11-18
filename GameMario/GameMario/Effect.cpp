#include "Effect.h"


Effect::Effect(void)
{
	_IsAlive = false;
	_Sprite = NULL;
}


Effect::~Effect(void)
{
}

bool Effect::CheckAlive() const
{
	return _IsAlive;
}
