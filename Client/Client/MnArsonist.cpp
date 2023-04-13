#include "MnArsonist.h"
#include "MnResources.h"
#include "MnTime.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnCollider.h"
#include "MnRigidbody.h"

namespace Mn
{
	Arsonist::Arsonist()
		: _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Collider(nullptr)
		, _MonStatus(eMonStatus::Idle)
		, _Dir(eDir::R)
		, _time(0)
	{
	}
	Arsonist::~Arsonist()
	{
	}
	void Arsonist::Initialize()
	{
		GameObject::SetName(L"Boss");

		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(400.0f, 400.0f));
		_Animator = AddComponent<Animator>();

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-12.0f*3,-35.0f*3));
		_Collider->Size(Vector2(24.0f*3, 35.0f*3));

		_Image = Resources::Load<Image>(L"Arsonist", L"..\\Resources\\Arsonist_Move.bmp");
		_Animator->CreateAnimation(L"walk_Left", _Image, Vector2::Zero, 13, 15,7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"walk_Right", _Image, Vector2(0,64), 13, 15, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Back_Step_Left", _Image, Vector2(0,64*2), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Back_Step_Right", _Image, Vector2(0,64*3), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"to_Charge_Left", _Image, Vector2(0, 64 * 4), 13, 15, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"to_Charge_Right", _Image, Vector2(0, 64 * 5), 13, 15, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Charge_Left", _Image, Vector2(0, 64 * 6), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Charge_Right", _Image, Vector2(0, 64 * 7), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fire_Left", _Image, Vector2(0, 64 * 8), 13, 15, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fire_Right", _Image, Vector2(0, 64 * 9), 13, 15, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hurt_Left", _Image, Vector2(0, 64 * 10), 13, 15, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hurt_Right", _Image, Vector2(48, 64 * 10), 13, 15, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"stab_Left", _Image, Vector2(0, 64 * 11), 13, 15, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"stab_Right", _Image, Vector2(0, 64 * 12), 13, 15, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, 64 * 13), 13, 15, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Idle_Right", _Image, Vector2(0, 64 * 14), 13, 15, 6, Vector2::Zero, 0.08);
		
		_Image = Resources::Load<Image>(L"Idle_Right", L"..\\Resources\\Arsonist_Attack.bmp");
		_Animator->CreateAnimation(L"Swip_Left", _Image, Vector2::Zero, 15, 2, 14,Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Swip_Right", _Image, Vector2(0,64), 15, 2, 14, Vector2::Zero, 0.08);
		_Animator->Play(L"Idle_Right",true);
		think();
		GameObject::Initialize();
	}
	void Arsonist::Update()
	{
		_time += Time::DeltaTime();
		if (_time >= 3.0f)
		{
			think();
			_time = 0.0f;
		}
		GameObject::Update();
	}
	void Arsonist::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Arsonist::Release()
	{
		GameObject::Release();
	}

	void Arsonist::animationCtrl()
	{
		switch (_MonStatus)
		{
		case eMonStatus::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Idle_Right", true);
			else
				_Animator->Play(L"Idle_Left", true);
			break;
		case eMonStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"walk_Right", true);
			else
				_Animator->Play(L"walk_Left", true);
			break;
		case eMonStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Swip_Right", false);
			else
				_Animator->Play(L"Swip_Left", false);
			break;
		case eMonStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Hurt_Right", true);
			else
				_Animator->Play(L"Hurt_Left", true);
			break;
		case eMonStatus::Skill:
			if (_Dir == eDir::R)
				_Animator->Play(L"Fire_Right", false);
			else
				_Animator->Play(L"Fire_Left", false);
			break;
		default:
			break;
		}
	}

	void Arsonist::think()
	{
		int think = rand() % 5;
		_MonStatus = eMonStatus(think);
		animationCtrl();
	}
}
