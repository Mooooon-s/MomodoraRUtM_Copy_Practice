#include "MnMonkey.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnCollider.h"
#include "MnTime.h"
#include "MnTransform.h"
namespace Mn
{
	Monkey::Monkey()
		: _Image(nullptr)
		, _Animator(nullptr)
		, _MonStatus(eMonStatus::Idle)
		, _Dir(eDir::R)
		, _Collider(nullptr)
		, _HurtTime(0.0f)
	{
	}
	Monkey::~Monkey()
	{
	}
	void Monkey::Initialize()
	{
		GameObject::SetName(L"Enemy");

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Vector2(700.0f, 400.0f);
		tr->Pos(pos);

		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(32 * 3, 32 * 3));
		_Collider->Center(Vector2(-16*3, -32*3));

		//44 32
		_Image = Resources::Load<Image>(L"Monkey", L"..\\Resources\\Monkey.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Monkey_Idle_Right", _Image, Vector2::Zero, 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Idle_Left", _Image, Vector2(0,32), 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Move_Right", _Image, Vector2::Zero, 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Move_Left", _Image, Vector2(0,32), 6, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Hurt_Right", _Image, Vector2(0,32*2), 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Hurt_Left", _Image, Vector2(0,32*3), 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Death_Right", _Image, Vector2(44,32*2), 6, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Death_Left", _Image, Vector2(44,32*3), 6, 4, 1, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Monkey_Attack", L"..\\Resources\\Monkey_Attack.bmp");
		_Animator->CreateAnimation(L"Monkey_Attack_Right", _Image, Vector2::Zero, 9, 2, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Monkey_Attack_Left", _Image, Vector2(0,48), 9, 2, 9, Vector2::Zero, 0.08);

		_Animator->Play(L"Monkey_Idle_Right", true);
		GameObject::Initialize();
	}
	void Monkey::Update()
	{
		switch (_MonStatus)
		{
		case Mn::Monkey::eMonStatus::Idle:
			idle();
			break;
		case Mn::Monkey::eMonStatus::Move:
			move();
			break;
		case Mn::Monkey::eMonStatus::Attack:
			attack();
			break;
		case Mn::Monkey::eMonStatus::Hurt:
			hurt();
			break;
		case Mn::Monkey::eMonStatus::Death:
			death();
			break;
		default:
			break;
		}
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
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			_MonStatus = eMonStatus::Hurt;
			animationCtrl();
		}
	}
	void Monkey::OnCollisionStay(Collider* other)
	{
	}
	void Monkey::OnCollisionExit(Collider* other)
	{
	}
	void Monkey::animationCtrl()
	{
		switch (_MonStatus)
		{
		case eMonStatus::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Monkey_Idle_Right", false);
			else
				_Animator->Play(L"Monkey_Idle_Left", false);
			break;
		case eMonStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Monkey_Move_Right", false);
			else
				_Animator->Play(L"Monkey_Move_Left", false);
			break;
		case eMonStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Monkey_Attack_Right", false);
			else
				_Animator->Play(L"Monkey_Attack_Left", false);
			break;
		case eMonStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Monkey_Hurt_Right", false);
			else
				_Animator->Play(L"Monkey_Hurt_Left", false);
			break;
		case eMonStatus::Death:
			if (_Dir == eDir::R)
				_Animator->Play(L"Monkey_Death_Right", false);
			else
				_Animator->Play(L"Monkey_Death_Left", false);
			break;
		default:
			break;
		}
	}
	void Monkey::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime >= 0.5)
		{
			_MonStatus = eMonStatus::Idle;
			animationCtrl();
			_HurtTime = 0;
		}
	}
	void Monkey::idle()
	{
	}
	void Monkey::attack()
	{
	}
	void Monkey::death()
	{
		this->State(GameObject::eState::Death);
	}
	void Monkey::move()
	{
	}
	void Monkey::afterHurt()
	{
		_MonStatus = eMonStatus::Idle;
		animationCtrl();
	}
	void Monkey::afterDeath()
	{
	}
	void Monkey::afterAttack()
	{
	}
}