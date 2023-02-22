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
		_image = Resources::Load<Image>(L"BackGround", L"..\\Resources\\BackGround.bmp");
		GameObject::Initialize();
	}
	void BG::Update()
	{
		GameObject::Update();
	}
	void BG::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, _image->Width(), _image->Height(), _image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
}
