#include "SwepAABB.h"


//---------------------------------------------
//lay vi tri o frame tiep theo cua box
//---------------------------------------------
Box getSweptBroadphaseBox(Box box)
{
	Box broadphasebox;

	broadphasebox.fX = box.fVx > 0 ? box.fX : box.fX + box.fVx;
	broadphasebox.fY = box.fVy > 0 ? box.fY : box.fY + box.fVy;
	broadphasebox.fWidth = box.fVx > 0 ? box.fVx + box.fWidth : box.fWidth - box.fVx;
	broadphasebox.fHeight = box.fVy > 0 ? box.fVy + box.fHeight : box.fHeight - box.fVy;
	broadphasebox.fVx = 0;
	broadphasebox.fVy = 0;

	return broadphasebox;
}

//----------------------------------------------------------
// returns true if the boxes are colliding (velocities are not used)
// dung trong truong hop xet va cham voi camera
//----------------------------------------------------------
bool AABBCheck(Box box1, Box box2)
{
	return !(box1.fX + box1.fWidth <= box2.fX || box1.fX >= box2.fX + box2.fWidth || box1.fY - box1.fHeight >= box2.fY || box1.fY <= box2.fY - box2.fHeight);
}

//--------------------------------------------------------------------------
//kiem tra va tranh va cham
//tra ve true neu va cham
//movex va movey la khoang cach ma b1 phai di chuyen de tranh va cham
//--------------------------------------------------------------------------
bool AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.fX - (b1.fX + b1.fWidth);
	float r = (b2.fX + b2.fWidth) - b1.fX;
	float t = b2.fY - (b1.fY - b1.fHeight);
	float b = (b2.fY - b2.fHeight) - b1.fY;

	// chưa xảy ra va chạm
	if (l > 0 || r < 0 || t < 0 || b > 0)
		return false;

	// tính dentry của x và y với mọi vx, vy
	moveX = abs(l) < r ? l : r;
	moveY = abs(b) < t ? b : t;

	// sử dụng biến move nào nhỏ hơn, biến còn lại cho bằng 0, 
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;
	return true;
}

//-------------------------------------------------------------
//tinh thoi gian va huong va cham
//tra ve (0, 1) neu va cham, tra ve 1 neu khong va cham
//normalx va normaly dung de xac dinh mat va cham
//--------------------------------------------------------------
float sweptAABB(Box box1, Box box2, float &normalx, float &normaly)
{
	//khoang cach vao mien dung do
	float xInvEntry, yInvEntry;

	//khoang cach thoat khoi mien dung do
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (box1.fVx > 0.0f)
	{
		xInvEntry = box2.fX - (box1.fX + box1.fWidth);
		xInvExit = (box2.fX + box2.fWidth) - box1.fX;
	}
	else
	{
		xInvEntry = (box2.fX + box2.fWidth) - box1.fX;
		xInvExit = box2.fX - (box1.fX + box1.fWidth);
	}

	if (box1.fVy > 0.0f)
	{
		yInvEntry = (box2.fY - box2.fHeight) - box1.fY;
		yInvExit = box2.fY - (box1.fY - box1.fHeight);
	}
	else
	{
		yInvEntry = box2.fY - (box1.fY - box1.fHeight);
		yInvExit = (box2.fY - box2.fHeight) - box1.fY;
	}

	//thoi gian vao mien va cham
	float xEntry, yEntry;

	//thoi gian ra khoi mien va cham
	float xExit, yExit;

	//neu van toc la 0 thi thoi gian va cham la vo cuc
	if (box1.fVx == 0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		//thoi gian = quang duong / van toc
		xEntry = xInvEntry / box1.fVx;
		xExit = xInvExit / box1.fVx;
	}

	//neu van toc la 0 thi thoi gian va cham la vo cuc
	if (box1.fVy == 0)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		//thoi gian = quang duong / van toc
		yEntry = yInvEntry / box1.fVy;
		yExit = yInvExit / box1.fVy;
	}

	//tim thoi gian bat dau va cham la thoi gian lon nhat
	float entryTime = max(xEntry, yEntry);

	//thoi gian ket thuc va cham la thoi gian nho nhat
	float exitTime = min(xExit, yExit);

	//truong hop khong xay ra va cham
	/*if (entryTime > exitTime)*/
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	//truong hop xay ra va cham
	else
	{
		if (xEntry > yEntry && (box1.fY - box1.fHeight != box2.fY))
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
	}
	return entryTime;
}