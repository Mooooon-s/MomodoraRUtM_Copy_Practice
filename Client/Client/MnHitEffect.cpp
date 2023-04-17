#include "MnHitEffect.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnTransform.h"

namespace Mn
{
	HitEffect::HitEffect()
		: GameObject()
		, _Animator(nullptr)
		, _Image(nullptr)
		, _IsEnd(false)
	{
	}
	HitEffect::~HitEffect()
	{
	}
	void HitEffect::Initialize()
	{
		_Animator = AddComponent<Animator>();
		_Image = Resources::Load<Image>(L"Hit_Effect_1", L"..\\Resources\\Effect_1.bmp");
		_Animator->CreateAnimation(L"Hit_Effect_last_Right", _Image, Vector2::Zero, 6, 2, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hit_Effect_last_Left", _Image, Vector2(0,32), 6, 2, 6, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Hit_Effect_2", L"..\\Resources\\Effect_2.bmp");
		_Animator->CreateAnimation(L"Hit_Effect_Jump_Right", _Image, Vector2::Zero, 5, 2, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hit_Effect_Jump_Left", _Image, Vector2(0,32), 5, 2, 5, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Hit_Effect_3", L"..\\Resources\\Effect_3.bmp");
		_Animator->CreateAnimation(L"Hit_Effect_front_Right", _Image, Vector2::Zero, 5, 2, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hit_Effect_front_Left", _Image, Vector2(0,32), 5, 2, 5, Vector2::Zero, 0.08);

		_Animator->GetCompleteEvent(L"Hit_Effect_last_Right") = std::bind(&HitEffect::Destroy, this);
		_Animator->GetCompleteEvent(L"Hit_Effect_last_Left") = std::bind(&HitEffect::Destroy, this);
		_Animator->GetCompleteEvent(L"Hit_Effect_Jump_Right") = std::bind(&HitEffect::Destroy, this);
		_Animator->GetCompleteEvent(L"Hit_Effect_Jump_Left") = std::bind(&HitEffect::Destroy, this);
		_Animator->GetCompleteEvent(L"Hit_Effect_front_Right") = std::bind(&HitEffect::Destroy, this);
		_Animator->GetCompleteEvent(L"Hit_Effect_front_Left") = std::bind(&HitEffect::Destroy, this);

		_Animator->Play(L"Hit_Effect_last_Right", false);

	}
	void HitEffect::Update()
	{
		if (_IsEnd)
			this->State(eState::Death);
		GameObject::Update();
	}
	void HitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HitEffect::Release()
	{
		GameObject::Release();
	}
	void HitEffect::Destroy()
	{
		_IsEnd = true;
	}
	void HitEffect::Dir(int dir)
	{
		if (dir == 0)
			_Dir = eDir::L;
		else
			_Dir = eDir::R;
	}
	void HitEffect::AnimationCntrl(int type)
	{
		switch (type)
		{
		case 0:
			if (_Dir == eDir::R)
				_Animator->Play(L"Hit_Effect_last_Right",false);
			else
				_Animator->Play(L"Hit_Effect_last_Left",false);
			break;
		case 1:
			if (_Dir == eDir::R)
				_Animator->Play(L"Hit_Effect_Jump_Right", false);
			else
				_Animator->Play(L"Hit_Effect_Jump_Left", false);
			break;
		case 2:
			if (_Dir == eDir::R)
				_Animator->Play(L"Hit_Effect_front_Right", false);
			else
				_Animator->Play(L"Hit_Effect_front_Left", false);
			break;
		default:
			break;
		}
	}
}