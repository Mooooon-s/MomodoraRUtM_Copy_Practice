#include "MnCath.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnRigidbody.h"
namespace Mn
{
	Cath::Cath()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Collider(nullptr)
	{
	}
	Cath::~Cath()
	{
	}
	void Cath::Initialize()
	{
		GameObject::SetName(L"NPC");

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Image = Resources::Load<Image>(L"Cath", L"..\\Resources\\cath.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Cath_Move_Right", _Image, Vector2::Zero, 8, 4, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Move_Left", _Image, Vector2(0,48), 8, 4, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Fight_Idle_Right", _Image, Vector2(0, 48*2), 8, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Fight_Idle_Left", _Image, Vector2(0, 48*3), 8, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Hurt_Right", _Image, Vector2(48 * 7, 48 * 2), 8, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Hurt_Left", _Image, Vector2(48 * 7, 48 * 3), 8, 4, 1, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Cath_Attack", L"..\\Resources\\cath_Attack.bmp");
		_Animator->CreateAnimation(L"Cath_Attack_Right", _Image, Vector2::Zero, 14, 2, 14, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Attack_Left", _Image, Vector2(0,48), 14, 2, 14, Vector2::Zero, 0.08);
		GameObject::Initialize();
	}
	void Cath::Update()
	{
		GameObject:: Update();
	}
	void Cath::Render(HDC hdc)
	{
		_Animator->Play(L"Cath_Fight_Idle_Right",true);
		GameObject::Render(hdc);
	}
	void Cath::Release()
	{
		GameObject::Release();
	}
	void Cath::OnCollisionEnter(Collider* other)
	{
	}
	void Cath::OnCollisionStay(Collider* other)
	{
	}
	void Cath::OnCollisionExit(Collider* other)
	{
	}
}