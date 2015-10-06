#pragma once

#include <algorithm>
#include <Windows.h>
#include "GlobalVariables.h"

struct Box
{
	float fX;
	float fY;
	float fWidth;//width
	float fHeight;//height
	float fVx;//veclocity x
	float fVy;//velocity y

	Box()
	{
		this->fX = 0;
		this->fY = 0;
		this->fWidth = 0;
		this->fHeight = 0;
		this->fVx = 0;
		this->fVy = 0;
	}
	Box(float x, float y, float width, float height)
	{
		this->fX = x;
		this->fY = y;
		this->fWidth = width;
		this->fHeight = height;
		this->fVx = 0;
		this->fVy = 0;
	}
	Box(float x, float y, float width, float height, float vx, float vy)
	{
		this->fX = x;
		this->fY = y;
		this->fWidth = width;
		this->fHeight = height;
		this->fVx = vx;
		this->fVy = vy;
	}

	void SetPosition(float x, float y){ fX = x; fY = y; }
	void SetVelocity(float vx, float vy){ fVx = vx; fVy = vy; }
	void SetContent(float width, float height){ fWidth = width; fHeight = height; }
};

//
float sweptAABB(Box box1, Box box2, float &normalx, float &nomaly);

//
Box getSweptBroadphaseBox(Box box);

//
bool AABBCheck(Box box1, Box box2);

//
bool AABB(Box box1, Box box2, float &moveX, float &moveY);