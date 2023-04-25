#include "MnPrayEffect.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnTransform.h"
#include "MnComponent.h"
#include "MnCamera.h"
namespace Mn
{
	PrayEffect::PrayEffect()
		: GameObject()
		, _Image(nullptr)
	{
	}
	PrayEffect::~PrayEffect()
	{
	}
	void PrayEffect::Initialize()
	{
		_Image = Resources::Load<Image>(L"PrayEffect", L"..\\resources\\pray_alpha.bmp");
		GameObject::Initialize();
	}
	void PrayEffect::Update()
	{
		GameObject::Update();
	}
	void PrayEffect::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		pos = Camera::ComputePos(pos);
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 127;
		AlphaBlend(hdc, pos.x - _Image->Width()/2.0f*3 , pos.y- _Image->Height() * 3, _Image->Width() * 3, _Image->Height() * 3, _Image->Hdc(), 0, 0, _Image->Width(), _Image->Height(), func);
		GameObject::Render(hdc);
	}
	void PrayEffect::Release()
	{
		GameObject::Release();
	}
}