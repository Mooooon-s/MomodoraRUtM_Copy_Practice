#include "MnFadeInOut.h"
#include "MnResources.h"
#include "MnTime.h"
#include "MnObject.h"

namespace Mn
{
	void FadeInOut::Initialize()
	{
		_Image = Resources::Load<Image>(L"Fade", L"..\\Resources\\Fade.bmp");
		_alpha = 255;
		_IsFade = true;
		// 연산량이 많다.
		func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = _alpha; // 0(투명) ~ 255(불투명) 알파값
	}
	void FadeInOut::Update()
	{
		if (_IsFade)
			FadeIN();
		else
			FadeOUT();

		if (_alpha >= 256 || _alpha <= -1)
			object::Destory(this);
	}
	void FadeInOut::Render(HDC hdc)
	{
		//_alpha -= Time::DeltaTime() * 255 * 0.7;
		func.SourceConstantAlpha = _alpha; // 0(투명) ~ 255(불투명) 알파값

		AlphaBlend(hdc, 0, 0, _Image->Width()*1.5f, _Image->Height()*1.5f, _Image->Hdc(), 0, 0, _Image->Width(), _Image->Height(), func);
		GameObject::Render(hdc);
	}
	void FadeInOut::Release()
	{
	}
	void FadeInOut::FadeIN()
	{
		_alpha -= Time::DeltaTime() * 255 * 0.7;
	}
	void FadeInOut::FadeOUT()
	{
		_alpha += Time::DeltaTime() * 255 * 0.7;
	}
}