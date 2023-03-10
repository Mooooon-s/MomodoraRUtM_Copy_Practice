#include "MnKaho_Cat.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnInput.h"
#include "MnTime.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnCollider.h"
#include "MnKaho.h"

namespace Mn
{
	Kaho_Cat::Kaho_Cat()
		:_PlayerStatus(ePlayerStatus::Idle)
		,_Animator(nullptr)
		,_Dir(eDir::R)
	{
	}
	Kaho_Cat::~Kaho_Cat()
	{
	}
	void Kaho_Cat::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos();

		Collider* col = AddComponent<Collider>();
		col->Size(Vector2(32.0f * 3, 32.0f * 3));
		col->Center(Vector2(-16.0f*3,-32.0f*3));
		
		_Animator = AddComponent<Animator>();
		Image* _Image = Resources::Load<Image>(L"Kaho_Cat", L"..\\Resources\\Kaho_Cat.bmp");
		_Animator->CreateAnimation(L"Cat_Attack_1_Right", _Image, Vector2(0, 0), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_1_Left", _Image, Vector2(0, 80), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_2_Right", _Image, Vector2(0, 80 * 2), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_2_Left", _Image, Vector2(0, 80 * 3), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_3_Right", _Image, Vector2(0, 80 * 4), 12, 6, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_3_Left", _Image, Vector2(0, 80 * 5), 12, 6, 12, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat2", L"..\\Resources\\Kaho_Cat_Move.bmp");
		_Animator->CreateAnimation(L"Cat_Idle_Right", _Image, Vector2(0, 0), 12, 8, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Idle_Left", _Image, Vector2(0, 32), 12, 8, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Hurt_Right", _Image, Vector2(32 * 12, 0), 12, 8, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Hurt_Left", _Image, Vector2(32 * 12, 32), 12, 8, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Death_Right", _Image, Vector2(0, 32 * 2), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Death_Left", _Image, Vector2(0, 32 * 3), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Crouch_Right", _Image, Vector2(0, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Crouch_Left", _Image, Vector2(0, 32 * 5), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Idle_Right", _Image, Vector2(32 * 4, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Idle_Left", _Image, Vector2(32 * 4, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Right", _Image, Vector2(0, 32 * 6), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Left", _Image, Vector2(0, 32 * 7), 12, 8, 9, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat3", L"..\\Resources\\Kaho_Cat_Move2.bmp");
		_Animator->CreateAnimation(L"Cat_Jump_Right", _Image, Vector2(0, 0), 9,11, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Jump_Left", _Image, Vector2(32, 0), 9, 11, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Run_Right", _Image, Vector2(32 * 2, 0), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Run_Left", _Image, Vector2(32 * 4, 0), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Fall_Right", _Image, Vector2(0, 32), 9, 11, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Fall_Left", _Image, Vector2(32 * 3, 32), 9, 11, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Land_Right", _Image, Vector2(0, 32 * 2), 9,11, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Land_Left", _Image, Vector2(32 * 4, 32 * 2), 9, 11, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Roll_Right", _Image, Vector2(0, 32 * 3), 9, 11, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Roll_Left", _Image, Vector2(0, 32 * 4), 9, 11, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Run_Right", _Image, Vector2(0, 32 * 5), 9, 11, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Run_Left", _Image, Vector2(0, 32 * 6), 9, 11, 6, Vector2::Zero, 0.08);

		//-------------------------------------------------------------------------------------------------------------------
		// 
		//													Events
		// 
		//-------------------------------------------------------------------------------------------------------------------
		_Animator->GetCompleteEvent(L"Cat_Attack_1_Right") = std::bind(&Kaho_Cat::attackComplete,this);
		_Animator->GetCompleteEvent(L"Cat_Attack_1_Left") = std::bind(&Kaho_Cat::attackComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Attack_2_Right") = std::bind(&Kaho_Cat::attackCombo1Complete, this);
		_Animator->GetCompleteEvent(L"Cat_Attack_2_Left") = std::bind(&Kaho_Cat::attackCombo1Complete, this);
		_Animator->GetCompleteEvent(L"Cat_Attack_3_Right") = std::bind(&Kaho_Cat::attackCombo2Complete, this);
		_Animator->GetCompleteEvent(L"Cat_Attack_3_Left") = std::bind(&Kaho_Cat::attackCombo2Complete, this);

		
		
		_Animator->Play(L"Cat_Idle_Right", true);
		
	}
	void Kaho_Cat::Update()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos = tr->Pos();
		switch (_PlayerStatus)
		{
		case ePlayerStatus::Idle:
			idle();
			break;
		case ePlayerStatus::Move:
			move();
			break;
		case ePlayerStatus::Attack:
			attack();
			break;
		case ePlayerStatus::Crouch:
			crouch();
			break;
		default:
			break;
		}

		tr->Pos(_Pos);
		GameObject::Update();
	}
	void Kaho_Cat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Kaho_Cat::Release()
	{
	}
	void Kaho_Cat::idle()
	{
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
			_PlayerStatus = ePlayerStatus::Move;
			animationCtrl();

		}
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
			_PlayerStatus = ePlayerStatus::Move;
			animationCtrl();

		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_PlayerStatus = ePlayerStatus::Crouch;
			animationCtrl();

		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
		
	}
	void Kaho_Cat::move()
	{
		//Run_to_Idle
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}

		//Move pos
		if (Input::GetKey(eKeyCode::Left))
			_Dir = eDir::L;
		if (Input::GetKey(eKeyCode::Right))
			_Dir = eDir::R;

		if (_Dir == eDir::L)
			_Pos.x -= 100.0f * Time::DeltaTime();
		else
			_Pos.x += 100.0f * Time::DeltaTime();
	}
	void Kaho_Cat::attack()
	{
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_Combo = true;
		}
	}
	void Kaho_Cat::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::Down)) {
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Cat::attackComplete()
	{

		if (_Combo)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Attack_2_Right", false);
			else
				_Animator->Play(L"Cat_Attack_2_Left", false);
		}
		else
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
		_Combo = false;
	}
	void Kaho_Cat::attackCombo1Complete()
	{
		if (_Combo)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Attack_3_Right", false);
			else
				_Animator->Play(L"Cat_Attack_3_Left", false);
		}
		else
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
		_Combo = false;
	}
	void Kaho_Cat::attackCombo2Complete()
	{
		_Combo=false;
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Cat::animationCtrl()
	{
		switch (_PlayerStatus)
		{
		case ePlayerStatus::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Idle_Right", true);
			else
				_Animator->Play(L"Cat_Idle_Left", true);
			break;
		case ePlayerStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Run_Right", true);
			else
				_Animator->Play(L"Cat_Run_Left", true);
			break;
		case ePlayerStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Attack_1_Right", false);
			else
				_Animator->Play(L"Cat_Attack_1_Left", false);
			break;
		case ePlayerStatus::Crouch:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Crouch_Right", true);
			else
				_Animator->Play(L"Cat_Crouch_Left", true);
			break;
		default:
			break;
		}
	}
}