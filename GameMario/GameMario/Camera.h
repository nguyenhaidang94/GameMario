#pragma once
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
	bool _IsPause;					//camera'll stop update if true
	bool _IsAutoMove;				//camera auto move
public:
	static Camera *GetInstance();
	Camera(void);
	~Camera(void);
	void SetWorldSize(D3DXVECTOR2 worldSize);
	void Update(D3DXVECTOR2 characterPosition);
	D3DXVECTOR2 GetViewPort() const;
	D3DXVECTOR2 GetWorldSize() const;
	Box GetBoundaryBox() const;
	Box GetActiveSite() const;
	//Pause if true/Unpause if false
	void PauseCamera(bool isPause);
	//Pause if true/Unpause if false
	void AutoMoveCamera(bool isAutoMove);
	//reset camera back to beginging position
	void Reset();
};

