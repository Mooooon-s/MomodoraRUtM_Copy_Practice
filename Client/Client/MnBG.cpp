#include "MnBG.h"
#include "MnResources.h"
#include "Application.h"
#include "MnCamera.h"
#include "MnTransform.h"

extern Mn::Application application;


namespace Mn {

	BG::BG()
		: _image(NULL)
		, _PreBitmap(nullptr)
		, _PreHDC(nullptr)
	{
	}

	BG::~BG()
	{
	}
	void BG::Initialize()
	{
		HDC mhdc = application.GetHdc();
		_image = Resources::Load<Image>(L"Play_BackGround", L"..\\Resources\\Stage1_BackGround_324_240.bmp");
		_PreBitmap = CreateCompatibleBitmap(mhdc, (_image->Width() / 4), _image->Height());
		_PreHDC = CreateCompatibleDC(mhdc);

		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(_PreHDC, _PreBitmap);
		DeleteObject(defaultBitmap);


		for (int i = 0; i < 4; i++)
		{
			GdiTransparentBlt(_PreHDC, 0, 0, _image->Width() / 4, _image->Height(), _image->Hdc(), 0+(324*i), 0, _image->Width() / 4, _image->Height(), RGB(0, 128, 128));
		}
		
		GameObject::Initialize();
	}
	void BG::Update()
	{
		GameObject::Update();
	}
	void BG::Render(HDC hdc)
	{
		Vector2 pos = Vector2::Zero;
		pos=Camera::ComputePos(Vector2::Zero);
		GdiTransparentBlt(hdc, pos.x, pos.y, (_image->Width()/4)*3, _image->Height() * 3, _PreHDC,0,0, _image->Width()/4, _image->Height(), SRCCOPY);
		GameObject::Render(hdc);
	}
}
