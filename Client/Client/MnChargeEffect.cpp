#include "MnChargeEffect.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnResources.h"

namespace Mn
{
	ChargeEffect::ChargeEffect()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Owner(nullptr)
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(-200.0f, -200.0f));
	}
	ChargeEffect::~ChargeEffect()
	{
	}
	void ChargeEffect::Initialize()
	{
		SetName(L"ChargeEffect");
		_Image = Resources::Load<Image>(L"Charge_Effect",L"..\\Resources\\Charge_Effect_alpha.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Charge_Effect_", _Image, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.08);
		_Animator->GetCompleteEvent(L"Charge_Effect_") = std::bind(&ChargeEffect::Done, this);
		_Animator->Play(L"Charge_Effect_", false);
		GameObject::Initialize();
	}
	void ChargeEffect::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* ownerTr = _Owner->GetComponent<Transform>();
		Vector2 pos = ownerTr->Pos();
		tr->Pos(pos);
		GameObject::Update();
	}
	void ChargeEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ChargeEffect::Release()
	{
		GameObject::Release();
	}
	void ChargeEffect::Done()
	{
		this->State(eState::Death);
	}
}