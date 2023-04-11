#include "MnMonkey.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnResources.h"
namespace Mn
{
	Monkey::Monkey()
		: _Image(nullptr)
		, _Animator(nullptr)
	{
	}
	Monkey::~Monkey()
	{
	}
	void Monkey::Initialize()
	{
		//44 32
		_Image = Resources::Load<Image>(L"Monkey", L"..\\Resources\\Monkey.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Monkey_Idle_Right", _Image, Vector2::Zero, 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Idle_Left", _Image, Vector2(0,32), 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Move_Right", _Image, Vector2::Zero, 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Move_Left", _Image, Vector2(0,32), 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_hurt_1_Right", _Image, Vector2(0,32*2), 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_hurt_1_Left", _Image, Vector2(0,32*3), 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_hurt_2_Right", _Image, Vector2(44,32*2), 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_hurt_2_Left", _Image, Vector2(44,32*3), 6, 4, 6, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Monkey_Attack", L"..\\Resources\\Monkey_Attack.bmp");
		_Animator->CreateAnimation(L"Monkey_Attack_Right", _Image, Vector2::Zero, 9, 2, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Attack_Left", _Image, Vector2(0,48), 9, 2, 9, Vector2::Zero, 0.08);

		_Animator->Play(L"Monkey_Idle_Right", true);
		GameObject::Initialize();
	}
	void Monkey::Update()
	{
		GameObject::Update();
	}
	void Monkey::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Monkey::Release()
	{
		GameObject::Release();
	}
	void Monkey::OnCollisionEnter(Collider* other)
	{
	}
	void Monkey::OnCollisionStay(Collider* other)
	{
	}
	void Monkey::OnCollisionExit(Collider* other)
	{
	}
}