#include "Effect.h"


Effect::Effect(void)
{
	_IsAlive = false;
}


Effect::~Effect(void)
{
}

bool Effect::CheckAlive()
{
	return _IsAlive;
}
