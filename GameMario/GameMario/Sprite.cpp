#include "Sprite.h"


Sprite::Sprite(void)
{
	_Image = NULL;
	_SpriteHandler = NULL;
}

Sprite::~Sprite(void)
{
}

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR Path, double Width, double Height, int Count, int SpritePerRow, D3DCOLOR TransparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;

	result = D3DXGetImageInfoFromFile(Path, &info);
	if (result != D3D_OK)
	{
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		Path,
		info.Width, 
		info.Height,
		1,				//Mipmap levels
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		TransparentColor,		// Transparent color
		&info,				// Image information
		NULL,
		&_Image);			// Result
	if (result != D3D_OK)
	{
		return;
	}
}

void Sprite::RenderAtFrame(float x, float y, int frameNo)
{
	RECT srect;

	srect.left = (frameNo % _SpritePerRow)*(_Width);
	srect.top = (frameNo / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	D3DXVECTOR3 position(x, y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -Camera::GetInstance()->GetViewPort().x;
	mt._42 = Camera::GetInstance()->GetViewPort().y;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);
	_SpriteHandler->End();
}

void Sprite::RenderFirstFrame(float x, float y)
{
	RECT srect;

	srect.left = 0;
	srect.top = 0;
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	D3DXVECTOR3 position(x, y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -Camera::GetInstance()->GetViewPort().x;
	mt._42 = Camera::GetInstance()->GetViewPort().y;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);
	_SpriteHandler->End();
}
 
void Sprite::Release()
{
	if (_Image != NULL)
		_Image->Release();

	if (_SpriteHandler != NULL)
		_SpriteHandler->Release();
}
