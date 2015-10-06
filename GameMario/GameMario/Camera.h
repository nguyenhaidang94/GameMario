#pragma once
#include "GlobalVariables.h"
#include <d3dx9.h>
#include "SwepAABB.h"

class Camera
{
private:
	int _WorldWidth, _WorldHeight;	//World size
	int _ViewPortX, _ViewPortY;		//Current viewport, Viewport if top-left conner of the screen
	int _OldX, _OldY;				//old position of camera to detect if character is going back
	bool _IsAllowBack;				//Is allow to going back or not
	static Camera *Instance;
public:
	static Camera *GetInstance();
	Camera(void);
	~Camera(void);
	void SetWorldSize(int worldWidth, int worldHeight);
	void Update(D3DXVECTOR2 characterPosition);
	D3DXVECTOR2 GetViewPort();
	D3DXVECTOR2 GetWorldSize();
	Box GetBoundaryBox();
};

