#include "MnUnderGroundBG.h"
#include "MnResources.h"
namespace Mn
{
	UnderGroundBG::UnderGroundBG()
		:GameObject()
		, _Image(nullptr)
	{
	}
	UnderGroundBG::~UnderGroundBG()
	{
	}
	void UnderGroundBG::Initialize()
	{
		_Image = Resources::Load<Image>(L"UnderGround_BackGround", L"..\\Resources\\Underground_stage.bmp");
	}
	void UnderGroundBG::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, _Image->Width(), _Image->Height(), _Image->Hdc(), 0, 0, SRCCOPY);
		GameObject::Render(hdc);
	}
}