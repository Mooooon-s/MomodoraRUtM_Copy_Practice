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
#include "MnRigidbody.h"

namespace Mn
{
	Kaho_Cat::Kaho_Cat()
		: _PlayerStatus(ePlayerStatus::Idle)
		, _Animator(nullptr)
		, _Dir(eDir::R)
		, _Combo(false)
		, _IsGround(true)
		, _Dashtime(0.0f)
	{
	}
	Kaho_Cat::~Kaho_Cat()
	{
	}
	void Kaho_Cat::Initialize()
	{
		GameObject::State(eState::Pause);
		Transform* tr = GetComponent<Transform>();
		tr->Pos();

		Collider* col = AddComponent<Collider>();
		col->Size(Vector2(20.0f * 3, 20.0f * 3));
		col->Center(Vector2(-10.0f*3,-20.0f*3));

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);
		
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
		_Animator->CreateAnimation(L"Cat_to_Idle_Left", _Image, Vector2(32 * 4, 32 * 5), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Right", _Image, Vector2(0, 32 * 6), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Left", _Image, Vector2(0, 32 * 7), 12, 8, 9, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat3", L"..\\Resources\\Kaho_Cat_Move2.bmp");
		_Animator->CreateAnimation(L"Cat_Jump_Right", _Image, Vector2(0, 0), 9,11, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Jump_Left", _Image, Vector2(48, 0), 9, 11, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Run_Right", _Image, Vector2(32 * 2, 0), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Run_Left", _Image, Vector2(32 * 4, 0), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Fall_Right", _Image, Vector2(0, 32), 9, 11, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Fall_Left", _Image, Vector2(48 * 3, 32), 9, 11, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Land_Right", _Image, Vector2(0, 32 * 2), 9,11, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Land_Left", _Image, Vector2(48 * 4, 32 * 2), 9, 11, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Roll_Right", _Image, Vector2(0, 32 * 3), 9, 11, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Roll_Left", _Image, Vector2(0, 32 * 4), 9, 11, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Run_Right", _Image, Vector2(0, 32 * 5), 9, 11, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Run_Left", _Image, Vector2(0, 32 * 6), 9, 11, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Break_Right", _Image, Vector2(0, 32 * 7), 9, 11, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Break_Left", _Image, Vector2(0, 32 * 8), 9, 11, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_PreDash_Right", _Image, Vector2(0, 32 * 9), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_PreDash_Left", _Image, Vector2(0, 32 * 10), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Dash_Right", _Image, Vector2(48*2, 32 * 9), 9, 11, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Dash_Left", _Image, Vector2(48*2, 32 * 10), 9, 11, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_PostDash_Right", _Image, Vector2(32*3, 32 * 9), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_PostDash_Left", _Image, Vector2(32*3, 32 * 10), 9, 11, 2, Vector2::Zero, 0.08);
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
		_Animator->GetCompleteEvent(L"Cat_Roll_Right") = std::bind(&Kaho_Cat::rollComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Roll_Left") = std::bind(&Kaho_Cat::rollComplete, this);
		_Animator->GetCompleteEvent(L"Cat_to_Crouch_Right") = std::bind(&Kaho_Cat::preCrouchComplete, this);
		_Animator->GetCompleteEvent(L"Cat_to_Crouch_Left") = std::bind(&Kaho_Cat::preCrouchComplete, this);
		_Animator->GetCompleteEvent(L"Cat_to_Idle_Right") = std::bind(&Kaho_Cat::postCrouchComplete, this);
		_Animator->GetCompleteEvent(L"Cat_to_Idle_Left") = std::bind(&Kaho_Cat::postCrouchComplete, this);
		_Animator->GetCompleteEvent(L"Cat_PreDash_Right") = std::bind(&Kaho_Cat::preDashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_PreDash_Left") = std::bind(&Kaho_Cat::preDashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Dash_Right") = std::bind(&Kaho_Cat::dashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Dash_Right") = std::bind(&Kaho_Cat::dashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_PostDash_Right") = std::bind(&Kaho_Cat::postDashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_PostDash_Right") = std::bind(&Kaho_Cat::postDashComplete, this);

		_Animator->GetCompleteEvent(L"Cat_Break_Right") = std::bind(&Kaho_Cat::RunComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Break_Left") = std::bind(&Kaho_Cat::RunComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Land_Right") = std::bind(&Kaho_Cat::landingComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Land_Left") = std::bind(&Kaho_Cat::landingComplete, this);


		

		_Animator->Play(L"Cat_Idle_Right", true);
		
	}
	void Kaho_Cat::Update()
	{
		if (GameObject::State()==eState::Active)
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
			case ePlayerStatus::Jump:
				jump();
				break;
			case ePlayerStatus::Crouch:
				crouch();
				break;
			case ePlayerStatus::Roll:
				roll();
				break;
			case ePlayerStatus::Fall:
				fall();
				break;
			default:
				break;
			}

			tr->Pos(_Pos);


			GameObject::Update();
		}
	}
	void Kaho_Cat::Render(HDC hdc)
	{
		if(GameObject::State() == eState::Active)
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
		if (Input::GetKeyDown(eKeyCode::A))
		{
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y -= 500.0f;

			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_PlayerStatus = ePlayerStatus::Crouch;
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_to_Crouch_Right",false);
			else
				_Animator->Play(L"Cat_to_Crouch_Left", false);
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_PlayerStatus = ePlayerStatus::Roll;
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
			if(_Dir==eDir::R)
				_Animator->Play(L"Cat_Break_Right", false);
			else
				_Animator->Play(L"Cat_Break_Left", false);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_PlayerStatus = ePlayerStatus::Roll;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y -= 500.0f;

			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}
		//Move pos
		if (Input::GetKey(eKeyCode::Left))
			_Dir = eDir::L;
		if (Input::GetKey(eKeyCode::Right))
			_Dir = eDir::R;

		if (_Dir == eDir::L)
			_Pos.x -= 500.0f * Time::DeltaTime();
		else
			_Pos.x += 500.0f * Time::DeltaTime();
	}
	void Kaho_Cat::attack()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		if (_Animator->GetActiveAnim()->IsComplete() == false && _IsGround == true)
		{
			if (Input::GetKeyDown(eKeyCode::S))
				_Combo = true;
		}
	}
	void Kaho_Cat::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::Down)) 
		{
			_PlayerStatus = ePlayerStatus::Idle;
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_to_Idle_Right", false);
			else
				_Animator->Play(L"Cat_to_Idle_Left", false);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
	}
	void Kaho_Cat::roll()
	{
		if (_IsGround == false)
		{
			_Dashtime += Time::DeltaTime();
		}
	}
	void Kaho_Cat::jump()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Pos.x -= 300.0f * Time::DeltaTime();
			_Dir = eDir::L;
			animationCtrl();
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			_Pos.x += 300.0f * Time::DeltaTime();
			_Dir = eDir::R;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_PlayerStatus = ePlayerStatus::Roll;
			animationCtrl();
		}

		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}
	}
	void Kaho_Cat::fall()
	{
		if (Input::GetKey(eKeyCode::Left))
			_Pos.x -= 300.0f * Time::DeltaTime();
		else if (Input::GetKey(eKeyCode::Right))
			_Pos.x += 300.0f * Time::DeltaTime();
		if (_Rigidbody->GetGround() == true)
		{
			_PlayerStatus = ePlayerStatus::Idle;
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Land_Right", false);
			else
				_Animator->Play(L"Cat_Land_Left", false);
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
	void Kaho_Cat::rollComplete()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Cat::preDashComplete()
	{
		if (_Dashtime >= 0.3)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Dash_Right", true);
			else
				_Animator->Play(L"Cat_Dash_Left", true);
		}
	}
	void Kaho_Cat::dashComplete()
	{
		if (_Dashtime >= 0.3)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_PostDash_Right", false);
			else
				_Animator->Play(L"Cat_PostDash_Left", false);
		}
	}
	void Kaho_Cat::postDashComplete()
	{
		if (_Dashtime >= 0.3)
		{
			_Dashtime = 0.0f;
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Cat::preCrouchComplete()
	{
		animationCtrl();
	}
	void Kaho_Cat::postCrouchComplete()
	{
		animationCtrl();
	}
	void Kaho_Cat::RunComplete()
	{
		PlayerStatus(ePlayerStatus::Idle);
		animationCtrl();
	}
	void Kaho_Cat::landingComplete()
	{
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
		case ePlayerStatus::Roll:
			if (_IsGround == true)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Roll_Right", false);
				else
					_Animator->Play(L"Cat_Roll_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_PreDash_Right", false);
				else
					_Animator->Play(L"Cat_PreDash_Right", false);
			}
			break;
		case ePlayerStatus::Jump:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Jump_Right", false);
			else
				_Animator->Play(L"Cat_Jump_Left", false);
			break;
		case ePlayerStatus::Crouch:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Crouch_Right", true);
			else
				_Animator->Play(L"Cat_Crouch_Left", true);
			break;
		case ePlayerStatus::Fall:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Fall_Right", false);
			else
				_Animator->Play(L"Cat_Fall_Left", false);
		default:
			break;
		}
	}
}