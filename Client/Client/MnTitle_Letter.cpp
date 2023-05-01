#include "MnTitle_Letter.h"
#include "MnResources.h"
#include "MnCamera.h"
namespace Mn
{
	Title_Letter::Title_Letter()
		: GameObject()
		, _Image(nullptr)
		, _CatImage(nullptr)
		, _StartFont(nullptr)
	{
	}
	Title_Letter::~Title_Letter()
	{
	}
	void Title_Letter::Initialize()
	{
		_Image =Resources::Load<Image>(L"Title_Latter", L"..\\Resources\\Game_Name.bmp");
		_CatImage =Resources::Load<Image>(L"Title_Cat_Logo", L"..\\Resources\\Log_Cat.bmp");
		_StartFont =Resources::Load<Image>(L"Title_Font", L"..\\Resources\\Start_Font.bmp");
		GameObject::Initialize();
	}
	void Title_Letter::Update()
	{
		GameObject::Update();
	}
	void Title_Letter::Render(HDC hdc)
	{
		Vector2 pos = Vector2(70 * 3, 65 * 3);
		pos = Camera::ComputePos(pos);
		GdiTransparentBlt(hdc, pos.x+50, pos.y- _CatImage->Height()*2, _CatImage->Width()*3, _CatImage->Height()*3, _CatImage->Hdc(), 0, 0, _CatImage->Width(), _CatImage->Height(), RGB(0, 128, 128));
		GdiTransparentBlt(hdc, pos.x, pos.y, _Image->Width()*3, _Image->Height()*3, _Image->Hdc(), 0, 0, 155, 46, RGB(0, 128, 128));
		GdiTransparentBlt(hdc, pos.x+100, 480, _StartFont->Width(), _StartFont->Height(), _StartFont->Hdc(), 0, 0, _StartFont->Width(), _StartFont->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void Title_Letter::Release()
	{
		GameObject::Release();
	}
}