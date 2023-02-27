#include "MnTitle_Letter.h"
#include "MnResources.h"

namespace Mn
{
	Title_Letter::Title_Letter()
		:_Image(NULL)
	{
	}
	Title_Letter::~Title_Letter()
	{
	}
	void Title_Letter::Initialize()
	{
		_Image =Resources::Load<Image>(L"Title_Latter", L"..\\Resources\\Game_Name.bmp");
		GameObject::Initialize();
	}
	void Title_Letter::Update()
	{
		GameObject::Update();
	}
	void Title_Letter::Render(HDC hdc)
	{
		GdiTransparentBlt(hdc, 70*3, 65*3, _Image->Width()*3, _Image->Height()*3, _Image->Hdc(), 0, 0, 155, 46, RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void Title_Letter::Release()
	{
		GameObject::Release();
	}
}