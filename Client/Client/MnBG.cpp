#include "MnBG.h"
#include "MnResources.h"
#include "Application.h"

extern Mn::Application application;


namespace Mn {

	BG::BG()
		:_image(NULL)
	{
	}

	BG::~BG()
	{
	}
	void BG::Initialize()
	{
		_image = Resources::Load<Image>(L"Play_BackGround", L"..\\Resources\\BackGround.bmp");
		GameObject::Initialize();
	}
	void BG::Update()
	{
		GameObject::Update();
	}
	void BG::Render(HDC hdc)
	{
		GdiTransparentBlt(hdc, 0, 0, _image->Width() * 3, _image->Height() * 3, _image->Hdc(),0,0, _image->Width(), _image->Height(), SRCCOPY);
		//BitBlt(hdc, 0, 0, _image->Width(), _image->Height(), _image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
}
