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
	

	int _CountTimeJump; //Biến đếm giúp cho việc nếu đè phím nhảy thì mario sẽ nhảy cao hơn
	bool _IsRight; //Xác định mario đang quay mặt qua trái hay phải
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
	bool _IsAnimationRight; //Xác định lúc nào mario tự động di chuyển qua phải
	bool _IsCollisionMonster; // Xác định mario va chạm với quái sẽ nhảy lên
	bool _IsDead; //Flag xác định mario còn sống hay đã chết
	bool _CanGoLeft;
	bool _CanGoRight;
	float _TimeBeforeTranferToSmall; //Biến đếm thời gian nhấp nháy từ mario big sang mario nhỏ
	bool _IsControl;//gắn Flag để biết có cho phép điều khiển mario hay ko
	bool _IsRender; //Gắn flag để xác định lúc ko cần vẽ mario ra màn hình

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

	
	bool GetIsControl(); //Get biến _IsControl
	bool SetIsControl(bool flag); //Set biến _IsControl
	bool GetFlagRender(); //Get biến _IsRender
	bool SetFlagRender(bool flag); //Set biến _IsRender

	//Mario state
	void Jump();
	void Fall();
	void Stand();
	void RunToRight();
	void RunToLeft();
	void PreStandRight();
	void PreStandLeft();
	void Sitting();
	void ChangeSpriteSitting();

	//Hiệu ứng chuyển đổi trạng thái của mario

	//Chuyển trạng thái từ mario small sang big
	void InitTranferSmallToBig();
	void TranferSmallToBig();
	void ExitTranferSmallToBig();

	//Chuyển trạng thái từ big sang small
	void InitTranferBigToSmall();
	void TranferBigToSmall();
	void ExitTranferBigToSmall();
	
	//Chuyển trạng thái từ big sang bắn súng
	void InitTranferBigToFlower();
	void TranferBigToFlower();
	void ExitTranferBigToFlower();

	void SetSpriteBeforeTransfromFlower();
	void SetSpriteShoot();

	//Trạng thái chết
	bool SetDead(bool flag);
	bool GetDead();
	void InitDead();
	void Dead();

	//Auto animation tự động trong game
	void AutoAnimationBottom();
	void AutoAnimationRight(D3DXVECTOR2 PositionEndAutoAnimation);
	void AutoAnimationEndGame();
	bool SetFlagAutoAnimationRight(bool flag);
	bool GetFlagAutoAnimationRight();
	

	//New
	//Get an instance of class mario
	static Mario *GetInstance();
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
};

