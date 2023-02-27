#include "MnTitleUI.h"
#include "MnResources.h"
#include "MnTime.h"

namespace Mn
{
	TitleUI::TitleUI()
		:_Image(NULL)
	{
	}
	TitleUI::~TitleUI()
	{
	}
	void TitleUI::Initialize()
	{
		_Image = Resources::Load<Image>(L"TitleName", L"..\\Resources\\Title_Animation.bmp");
		GameObject::Initialize();
	}
	void TitleUI::Update()
	{
		GameObject::Update();
	}
	void TitleUI::Render(HDC hdc)
	{
		_Time += Time::DeltaTime();

		if (_Idx >= 4)
		{
			_Idx = 0;
		}

		if (_Time > 0.15f)
		{
			_Idx++;
			_Time = 0.0f;
		}
		GdiTransparentBlt(hdc, 564, 570, 136 * 3, 54 * 3, _Image->Hdc(), 1, (54*_Idx), 136, 54, SRCCOPY);
		//BitBlt(hdc, 100, 100, _image->Width(), _image->Height(), _image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
	void TitleUI::Release()
	{
		GameObject::Release();
	}
}