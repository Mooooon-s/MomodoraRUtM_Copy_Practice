#include "MnTitleBG.h"
#include "MnResources.h"
#include "Application.h"
#include "MnCamera.h"
#include "MnTransform.h"

extern Mn::Application application;

namespace Mn
{
	TitleBG::TitleBG()
		: _Image(NULL)
	{
	}
	TitleBG::~TitleBG()
	{
	}
	void TitleBG::Initialize()
	{
		_Image = Resources::Load<Image>(L"Title_BackGround", L"..\\Resources\\Title_Scene.bmp");
		GameObject::Initialize();
	}
	void TitleBG::Update()
	{
		GameObject::Update();
	}
	void TitleBG::Render(HDC hdc)
	{
		Vector2 pos = Vector2::Zero;
		pos = Camera::ComputePos(Vector2::Zero);
		GdiTransparentBlt(hdc, pos.x, pos.y, _Image->Width()*3.0f, _Image->Height()*3.0f, _Image->Hdc(), 0, 0, _Image->Width(), _Image->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
}