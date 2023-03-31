#include "MnImp.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnKaho.h"

namespace Mn
{
	Imp::Imp()
		:_Animator(nullptr)
		,_Collider(nullptr)
		,_Rigidbody(nullptr)
		,_Pos(Vector2::Zero)
		,_Status(eMonStatus::Move)
		,_Time(0)
		,_Hp(3)
	{
	}
	Imp::~Imp()
	{
	}
	void Imp::Initialize()
	{
		GameObject::SetName(L"Enemy");
		Transform* tr = GetComponent<Transform>();
		_Pos = Vector2(700.0f, 400.0f);
		tr->Pos(_Pos);

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-10*3,-20*3));
		_Collider->Size(Vector2(20*3, 20*3));

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0);
		_Rigidbody->SetGround(false);

		Image* _Image = Resources::Load<Image>(L"Imp", L"..\\Resources\\Imp.bmp");
		_Animator = AddComponent<Animator>();
		
		_Animator->CreateAnimation(L"Imp_Idle_Right", _Image, Vector2::Zero, 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Idle_Left", _Image, Vector2(32,0), 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Hurt_Right", _Image, Vector2(32*2, 0), 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Hurt_Left", _Image, Vector2(32*3, 0), 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Walk_Right", _Image, Vector2(0, 32), 8, 5, 5, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Walk_Left", _Image, Vector2(0, 32*2), 8, 5, 5, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Attack_Right", _Image, Vector2(0, 32*3), 8, 5, 8, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Attack_Left", _Image, Vector2(0, 32 * 4), 8, 5, 8, Vector2::Zero, 0.1f);

		_Animator->Play(L"Imp_Idle_Right", true);

		GameObject::Initialize();
	}
	void Imp::Update()
	{
		switch (_Status)
		{
		case eMonStatus::Move:
			move();
			break;
		case eMonStatus::Attack:
			attack();
			break;
		case eMonStatus::Defence:
			defence();
			break;
		case eMonStatus::Hurt:
			hurt();
			break;
		default:
			break;
		}
		if (_Hp <= 0)
			GameObject::State(eState::Death);
		GameObject::Update();
	}
	void Imp::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Imp::Release()
	{
		GameObject::Release();
	}
	void Imp::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			_Status=eMonStatus::Hurt;
			animationCntrl();
			_Hp -= 1;
			_Time = 0;
		}
	}
	void Imp::OnCollisionStay(Collider* other)
	{
	}
	void Imp::OnCollisionExit(Collider* other)
	{
	}
	void Imp::move()
	{

	}
	void Imp::attack()
	{

	}
	void Imp::defence()
	{

	}
	void Imp::hurt()
	{
		_Time += Time::DeltaTime();
		if (_Time >= 0.5)
		{
			_Status = eMonStatus::Defence;
			animationCntrl();
			_Time = 0;
		}
	}
	void Imp::animationCntrl()
	{
		switch (_Status)
		{
		case eMonStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Walk_Right", true);
			else
				_Animator->Play(L"Imp_Walk_Left", true);
			break;
		case eMonStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Attack_Right", false);
			else
				_Animator->Play(L"Imp_Attack_Left", false);
			break;
		case eMonStatus::Defence:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Idle_Right", false);
			else
				_Animator->Play(L"Imp_Idle_Left", false);
			break;
		case eMonStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Hurt_Right", false);
			else
				_Animator->Play(L"Imp_Hurt_Right", false);
			break;
		default:
			break;
		}
	}
	Imp::eMonStatus Imp::think()
	{
		int behave = 0;
		behave = rand() % 3;
		return eMonStatus(behave);
	}
}