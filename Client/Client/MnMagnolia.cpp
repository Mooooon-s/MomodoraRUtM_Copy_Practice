#include "MnMagnolia.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnRigidbody.h"
namespace Mn
{
	Magnolia::Magnolia()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
	{
	}
	Magnolia::~Magnolia()
	{
	}
	void Magnolia::Initialize()
	{
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Image = Resources::Load<Image>(L"Magnolia_Arrow", L"..\\Resources\\Magnolia_Arrow.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Magnolia_Arrow_Idle_Left", _Image, Vector2::Zero, 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Idle_Right", _Image, Vector2(0,48), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Attack_Left", _Image, Vector2(0,48*2), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Attack_Right", _Image, Vector2(0,48*3), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Land_Left", _Image, Vector2(0, 48 * 4), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Land_Right", _Image, Vector2(0, 48 * 5), 6, 6, 6, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Magnolia_Knife", L"..\\Resources\\Magnolia_knife.bmp");
		_Animator->CreateAnimation(L"Magnolia_Knife_Idle_Left", _Image, Vector2::Zero, 4, 4, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Idle_Right", _Image, Vector2(0, 48), 4, 4, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Hurt_Left", _Image, Vector2(0, 48 * 2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_hurt_Right", _Image, Vector2(0, 48 * 3), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Death_Left", _Image, Vector2(48, 48 * 2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Death_Right", _Image, Vector2(48, 48 * 2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->Play(L"Magnolia_Arrow_Idle_Left", true);
		GameObject::Initialize();
	}
	void Magnolia::Update()
	{
		GameObject::Update();
	}
	void Magnolia::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Magnolia::Release()
	{
		GameObject::Release();
	}
	void Magnolia::OnCollisionEnter(Collider* other)
	{
	}
	void Magnolia::OnCollisionStay(Collider* other)
	{
	}
	void Magnolia::OnCollisionExit(Collider* other)
	{
	}
}