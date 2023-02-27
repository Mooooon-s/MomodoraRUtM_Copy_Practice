#include "MnTitleUI.h"
#include "MnResources.h"

namespace Mn
{
	TitleUI::TitleUI()
		:_image(NULL)
	{
	}
	TitleUI::~TitleUI()
	{
	}
	void TitleUI::Initialize()
	{
		_image = Resources::Load<Image>(L"TitleName", L"..\\Resources\\Title_Animation.bmp");
		GameObject::Initialize();
	}
	void TitleUI::Update()
	{
		GameObject::Update();
	}
	void TitleUI::Render(HDC hdc)
	{
		BitBlt(hdc, 100, 100, _image->Width(), _image->Height(), _image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
	void TitleUI::Release()
	{
		GameObject::Release();
	}
}