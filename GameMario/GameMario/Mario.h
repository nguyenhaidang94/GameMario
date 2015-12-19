#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "GameStatistics.h"
#include "Unility.h"
#include "Gun.h"
#include "FloatingBar.h"

class Mario : public DynamicGameObject
{
private:
	int _CurrentFrame;
	eMarioState _State;
	eMarioState _PreState;
	bool _IsCollide;	//check if collided with ground
	D3DXVECTOR2 _CollisionPoint; 
	eGameTag _PipeTag;	//if mario stand on pipe with tag can go to another world, store tag here
	eGameTag _BrickTag;

	static Mario *Instance;
	

	int _CountTimeJump;
	bool _IsRight;
	DWORD _Frame_start;	
	DWORD _Tick_per_frame; //FPS của mario
	DWORD _Tick_per_frame_animation; //FPS lúc auto aniamtion
	bool _IsGetMushroom;		//Lấy nấm
	bool _IsGetStar;			//Lấy ngôi sao
	bool _IsTranferToSmall;		//Xác định biến mario to thành mario nhỏ
	bool _IsGetFlowerToTranform;//Xác định chuyển đổi từ bình thường qua mario bất tử
	bool _IsFlower;				//Xác định mario ăn hoa để bắn súng
	int _CountStar;            //Xác định thời gian bất tử
	int _currentFrameBeforeTransformToFlower;// Xác định frame trước khi ăn sao để xét sprite sau khi ăn sao
	bool _IsAnimationPipe; // Xác định mario bắt đầu thực hiện animation lúc rớt xuống cống
	bool _IsAnimationFlag; //Xác định mario bắt đầu thực hiện animation lúc lấy lá cờ
	bool _IsAnimationRight;
	bool _IsCollisionMonster; // Xác định mario va chạm với quái sẽ nhảy lên
	bool _IsFloatingBarCollision;
	bool _IsDead;
	bool _CanGoLeft;
	bool _CanGoRight;
	float _TimeBeforeTranferToSmall;
	float _VelocityFloatingBar;
	bool _IsControl;

public:
	Mario(void);
	~Mario(void);
	//Inherited function
	Box GetMovementRangeBox();
	Box GetBoundaryBox();
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
	//handle collision using offset
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection, float offsetX, float offsetY);

	//Mario state
	bool GetIsControl();
	bool SetIsControl(bool flag);
	void Jump();
	void Fall();
	void Stand();
	void RunToRight();
	void RunToLeft();
	void PreStandRight();
	void PreStandLeft();
	void Sitting();
	void TranferSmallToBig();
	void TranferBigToSmall();
	void Dead();

	//state flower man
	void TranferBigToFlower();
	void SetSpriteBeforeTransfromFlower();
	void SetSpriteShoot();
	void AutoAnimationBottom();
	void AutoAnimationRight(D3DXVECTOR2 PositionEndAutoAnimation);
	void AutoAnimationEndGame();
	bool SetFlagAutoAnimationRight(bool flag);
	bool GetFlagAutoAnimationRight();
	bool SetDead(bool flag);

	//New
	//Get an instance of class mario
	static Mario *GetInstance();
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
};

