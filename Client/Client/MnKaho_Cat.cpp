#include "MnKaho.h"
#include "MnKaho_Cat.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnInput.h"
#include "MnTime.h"
#include "MnMeleeEffect.h"
#include "MnObject.h"

#include "MnComponent.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnRigidbody.h"

#include "MnKnife.h"
#include "MnMonMeleeAttack.h"
#include "MnStaff.h"

#include "MnFireBall.h"
#include "MnFireFlame.h"
#include "MnFlame.h"

#include "MnLupiarBall.h"
#include "MnMagArrow.h"

#include "MnChargeEffect.h"
#include "MnItemBox.h"
#include "MnWall.h"

namespace Mn
{
	Kaho_Cat::Kaho_Cat()
		: _PlayerStatus(ePlayerStatus::Idle)
		, _Rigidbody(nullptr)
		, _State(eState::Pause)
		, _Animator(nullptr)
		, _Dir(eDir::R)
		, _Dashtime(0.0f)
		, _HurtTime(0.0f)
		, _AlphaTime(0.0f)
		, _DamageTime(0.0f)
		, _Jumpforce(550.0f)
		, _MoveSpeed(0.0f)
		, _CoolTime(0.0f)
		, _Switch(false)
		, _Combo(false)
		, _Death(false)
		, _DashOn(true)
		, _GetDamage(true)
		, _AlphaDegree(90)
		, _DoubleJump(0)
		, _ComboCount(0)
		, _Hp(100)
		, _RevivalPos(Vector2::Zero)
	{
	}
	Kaho_Cat::~Kaho_Cat()
	{
	}
	void Kaho_Cat::Initialize()
	{
		GameObject::SetName(L"Player");
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
		Image* _Image = Resources::Load<Image>(L"Kaho_Cat", L"..\\Resources\\Kaho_Cat_alpha.bmp");
		_Animator->CreateAnimation(L"Cat_Attack_1_Right", _Image, Vector2(0, 0), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_1_Left", _Image, Vector2(0, 80), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_2_Right", _Image, Vector2(0, 80 * 2), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_2_Left", _Image, Vector2(0, 80 * 3), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_3_Right", _Image, Vector2(0, 80 * 4), 12, 6, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_3_Left", _Image, Vector2(0, 80 * 5), 12, 6, 12, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat2", L"..\\Resources\\Kaho_Cat_Move_alpha.bmp");
		_Animator->CreateAnimation(L"Cat_Idle_Right", _Image, Vector2(0, 0), 12, 8, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Idle_Left", _Image, Vector2(0, 32), 12, 8, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Hurt_Right", _Image, Vector2(32 * 11, 0), 12, 8, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Hurt_Left", _Image, Vector2(32 * 11, 32), 12, 8, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Death_Right", _Image, Vector2(0, 32 * 2), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Death_Left", _Image, Vector2(0, 32 * 3), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Crouch_Right", _Image, Vector2(0, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Crouch_Left", _Image, Vector2(0, 32 * 5), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_UseItem_Right", _Image, Vector2(0, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_UseItem_Left", _Image, Vector2(0, 32 * 5), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Idle_Right", _Image, Vector2(32 * 4, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Idle_Left", _Image, Vector2(32 * 4, 32 * 5), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Right", _Image, Vector2(0, 32 * 6), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Left", _Image, Vector2(0, 32 * 7), 12, 8, 9, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat3", L"..\\Resources\\Kaho_Cat_Move2_alpha.bmp");
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
		_Animator->CreateAnimation(L"Cat_PostDash_Right", _Image, Vector2(48*3, 32 * 9), 9, 11, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_PostDash_Left", _Image, Vector2(48*3, 32 * 10), 9, 11, 2, Vector2::Zero, 0.08);
		//-------------------------------------------------------------------------------------------------------------------
		// 
		//													Events
		// 
		//-------------------------------------------------------------------------------------------------------------------
		_Animator->GetStartEvent(L"Cat_Attack_1_Right") = std::bind(&Kaho_Cat::attackStart, this);
		_Animator->GetStartEvent(L"Cat_Attack_1_Left") = std::bind(&Kaho_Cat::attackStart, this);
		_Animator->GetStartEvent(L"Cat_Attack_2_Right") = std::bind(&Kaho_Cat::attackCombo1Start, this);
		_Animator->GetStartEvent(L"Cat_Attack_2_Left") = std::bind(&Kaho_Cat::attackCombo1Start, this);
		_Animator->GetStartEvent(L"Cat_Attack_3_Right") = std::bind(&Kaho_Cat::attackCombo2Start, this);
		_Animator->GetStartEvent(L"Cat_Attack_3_Left") = std::bind(&Kaho_Cat::attackCombo2Start, this);

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
		_Animator->GetCompleteEvent(L"Cat_Dash_Left") = std::bind(&Kaho_Cat::dashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_PostDash_Right") = std::bind(&Kaho_Cat::postDashComplete, this);
		_Animator->GetCompleteEvent(L"Cat_PostDash_Left") = std::bind(&Kaho_Cat::postDashComplete, this);

		_Animator->GetCompleteEvent(L"Cat_Break_Right") = std::bind(&Kaho_Cat::RunComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Break_Left") = std::bind(&Kaho_Cat::RunComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Land_Right") = std::bind(&Kaho_Cat::landingComplete, this);
		_Animator->GetCompleteEvent(L"Cat_Land_Left") = std::bind(&Kaho_Cat::landingComplete, this);


		_Animator->FindAnimation(L"Cat_UseItem_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&Kaho_Cat::useItem, this);
		_Animator->FindAnimation(L"Cat_UseItem_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&Kaho_Cat::useItem, this);
		_Animator->GetCompleteEvent(L"Cat_UseItem_Right") = std::bind(&Kaho_Cat::afterUseItem, this);
		_Animator->GetCompleteEvent(L"Cat_UseItem_Left") = std::bind(&Kaho_Cat::afterUseItem, this);
		_Animator->GetCompleteEvent(L"Cat_Death_Right") = std::bind(&Kaho_Cat::afterDeath, this);
		_Animator->GetCompleteEvent(L"Cat_Death_Left") = std::bind(&Kaho_Cat::afterDeath, this);

		_Animator->Play(L"Cat_Idle_Right", true);
		
	}
	void Kaho_Cat::Update()
	{
		if (_RevivalPos == Vector2::Zero)
		{
			Transform* tr = GetComponent<Transform>();
			_RevivalPos = tr->Pos();
		}
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
			case ePlayerStatus::UseItem:
				//useItem();
				break;
			case ePlayerStatus::Hurt:
				hurt();
				break;
			default:
				break;
			}


			if (_DashOn == false)
			{
				_CoolTime -= Time::DeltaTime();
				if (_CoolTime < 0.0f)
				{
					ChargeEffect* effect = object::Instantiate<ChargeEffect>(Vector2(_Pos.x, _Pos.y - (24 * 3)), eLayerType::ChargeEffect);
					effect->GetOwnerObject(this);
					_DashOn = true;
				}
			}

			tr->Pos(_Pos);
			_AlphaTime += Time::DeltaTime();

			if (_DoubleJump != 0 && _Rigidbody->GetGround() == true)
				_DoubleJump = 0;
			if (_Hp <= 0 && _Death == false)
			{
				_Death = true;
				_PlayerStatus = ePlayerStatus::Death;
				animationCtrl();
			}

			GameObject::Update();
		}
	}
	void Kaho_Cat::Render(HDC hdc)
	{
		if (GameObject::State() == eState::Active)
		{
			if (_GetDamage == false)
			{
				alpha();
				_DamageTime += Time::DeltaTime();
			}
			GameObject::Render(hdc);
		}
	}
	void Kaho_Cat::Release()
	{
	}
	//-------------------------------------------------------------------------------------------------------------------
	//
	//													Collider
	// 
	//-------------------------------------------------------------------------------------------------------------------
	void Kaho_Cat::OnCollisionEnter(Collider* other)
	{
		if (_Death == false)
		{

			if (other->Owner()->GetName() == L"Enemy" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_Hp -= 15;
				_GetDamage = false;
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}
			if (other->Owner()->GetName() == L"Boss" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_Hp -= 15;
				_GetDamage = false;
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}
			if (other->Owner()->GetName() == L"Throws" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				if (dynamic_cast<Knife*>(other->Owner()))
				{
					_Hp -= 15;
					dynamic_cast<Knife*>(other->Owner())->Hit();
					_GetDamage = false;
					_PlayerStatus = ePlayerStatus::Hurt;
					animationCtrl();
				}
				if (dynamic_cast<MonMeleeAttack*>(other->Owner())
					|| dynamic_cast<Staff*>(other->Owner())
					|| dynamic_cast<Flame*>(other->Owner())
					|| dynamic_cast<MagArrow*>(other->Owner())
					|| dynamic_cast<FireBall*>(other->Owner())
					|| dynamic_cast<FireFlame*>(other->Owner())
					|| dynamic_cast<LupiarBall*>(other->Owner()))
				{
					_Hp -= 15;
					_GetDamage = false;
					_PlayerStatus = ePlayerStatus::Hurt;
					animationCtrl();
				}
			}
		}
	}
	void Kaho_Cat::OnCollisionStay(Collider* other)
	{
		if (_Death == false)
		{
			if (other->Owner()->GetName() == L"Enemy" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_Hp -= 15;
				_GetDamage = false;
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}

			if (other->Owner()->GetName() == L"Boss" && _GetDamage == true && _PlayerStatus != ePlayerStatus::Roll)
			{
				_Hp -= 15;
				_GetDamage = false;
				_PlayerStatus = ePlayerStatus::Hurt;
				animationCtrl();
			}

			if (other->Owner()->GetName() == L"Wall")
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->Pos();
				if (_Dir == eDir::R)
				{
					pos.x -= _MoveSpeed * Time::DeltaTime();
					tr->Pos(pos);
				}
				else
				{
					pos.x += _MoveSpeed * Time::DeltaTime();
					tr->Pos(pos);
				}

			}
		}
	}
	//-------------------------------------------------------------------------------------------------------------------
	//
	//													FSM
	// 
	//-------------------------------------------------------------------------------------------------------------------
	void Kaho_Cat::idle()
	{
		if (Input::GetKey(eKeyCode::Right))
		{
			_MoveSpeed = 500.0f;
			_Dir = eDir::R;
			_PlayerStatus = ePlayerStatus::Move;
			animationCtrl();

		}
		if (Input::GetKey(eKeyCode::Left))
		{
			_MoveSpeed = 500.0f;
			_Dir = eDir::L;
			_PlayerStatus = ePlayerStatus::Move;
			animationCtrl();

		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			_MoveSpeed = 300.f;
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y -= _Jumpforce;
			_DoubleJump++;
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
			if (_Rigidbody->GetGround() == true)
			{
				_MoveSpeed = 300.0f;
			}
			else
			{
				_MoveSpeed = 1000.0f;
			}
			_PlayerStatus = ePlayerStatus::Roll;
			animationCtrl();
		}
		
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_PlayerStatus = ePlayerStatus::UseItem;
			animationCtrl();
		}
		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}
	}
	void Kaho_Cat::move()
	{
		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}

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
			_MoveSpeed = 300.0f;
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y -= _Jumpforce;
			_DoubleJump++;
			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_PlayerStatus = ePlayerStatus::UseItem;
			animationCtrl();
		}
		//Move pos
		if (Input::GetKey(eKeyCode::Left))
			_Dir = eDir::L;
		if (Input::GetKey(eKeyCode::Right))
			_Dir = eDir::R;

		if (_Dir == eDir::L)
			_Pos.x -= _MoveSpeed * Time::DeltaTime();
		else
			_Pos.x += _MoveSpeed * Time::DeltaTime();
	}
	void Kaho_Cat::attack()
	{
		if (_ComboCount == 1)
		{
			if (_Dir == eDir::L)
				_Pos.x -= 30.0f * Time::DeltaTime();
			else if (_Dir == eDir::R)
				_Pos.x += 30.0f * Time::DeltaTime();
		}
		else if (_ComboCount == 2)
		{
			if (_Dir == eDir::L)
				_Pos.x -= 15.0f * Time::DeltaTime();
			else if (_Dir == eDir::R)
				_Pos.x += 15.0f * Time::DeltaTime();
		}
		else if (_ComboCount == 3)
		{
			if (_Dir == eDir::L)
				_Pos.x -= 80.0f * Time::DeltaTime();
			else if (_Dir == eDir::R)
				_Pos.x += 80.0f * Time::DeltaTime();
		}
		if (_Animator->GetActiveAnim()->IsComplete() == false && _Rigidbody->GetGround()==true)
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
		if (_Rigidbody->GetGround() == true)
		{
			if (_Dir == eDir::R)
				_Pos.x += _MoveSpeed * Time::DeltaTime();
			else
				_Pos.x -= _MoveSpeed * Time::DeltaTime();
		}
		else
		{
			_Rigidbody->Velocity(Vector2(0.0f, 0.0f));
			_Dashtime += Time::DeltaTime();

			if (_Dashtime >= 0.3f)
			{
				if (_Dir == eDir::R)
					_Pos.x += _MoveSpeed * Time::DeltaTime();
				else
					_Pos.x -= _MoveSpeed * Time::DeltaTime();
			}
		}
	}
	void Kaho_Cat::jump()
	{

		if (Input::GetKeyDown(eKeyCode::A)&&_DoubleJump<=1)
		{
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y = 0;
			velocity.y -= _Jumpforce;
			_DoubleJump++;
			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			_Pos.x -= _MoveSpeed * Time::DeltaTime();
			_Dir = eDir::L;
			animationCtrl();
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			_Pos.x += _MoveSpeed * Time::DeltaTime();
			_Dir = eDir::R;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::Q) && _DashOn == true )
		{
			_DashOn = false;
			_CoolTime = 1.5f;
			if (_Rigidbody->GetGround() == true)
			{
				_MoveSpeed = 300.0f;
			}
			else
			{
				_MoveSpeed = 1000.0f;
			}
			_PlayerStatus = ePlayerStatus::Roll;
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_PreDash_Right", false);
			else
				_Animator->Play(L"Cat_PreDash_Left", false);
		}

		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_MoveSpeed = 300.f;
			_PlayerStatus = ePlayerStatus::Fall;
			animationCtrl();
		}
	}
	void Kaho_Cat::fall()
	{
		if (Input::GetKeyDown(eKeyCode::A) && _DoubleJump <= 1)
		{
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y = 0;
			velocity.y -= _Jumpforce;
			_DoubleJump++;
			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::Q) && _DashOn == true )
		{
			_DashOn = false;
			_CoolTime = 1.5f;
			_MoveSpeed = 800.0f;
			_PlayerStatus = ePlayerStatus::Roll;
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_PreDash_Right", false);
			else
				_Animator->Play(L"Cat_PreDash_Left", false);
		}
		if (Input::GetKey(eKeyCode::Left))
			_Pos.x -= _MoveSpeed * Time::DeltaTime();
		else if (Input::GetKey(eKeyCode::Right))
			_Pos.x += _MoveSpeed * Time::DeltaTime();
		
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
		
		if (_Rigidbody->GetGround() == true)
		{
			_PlayerStatus = ePlayerStatus::Idle;
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Land_Right", false);
			else
				_Animator->Play(L"Cat_Land_Left", false);
		}
	}
	void Kaho_Cat::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime < 0.7)
		{
			if (_Dir == eDir::R)
			{
				_Pos.x -= 100.0f * Time::DeltaTime();
				_Pos.y -= 100.0f * Time::DeltaTime();
			}
			else
			{
				_Pos.x += 100.0f * Time::DeltaTime();
				_Pos.y -= 100.0f * Time::DeltaTime();
			}
		}
		else
		{
			_HurtTime = 0.0;
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Cat::useItem()
	{
		ItemBox* item = nullptr;
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> itemObj = scene->GetGameObject(eLayerType::UI);
		for (auto v : itemObj)
		{
			if (dynamic_cast<ItemBox*>(v))
			{
				item = dynamic_cast<ItemBox*>(v);
			}
		}
		if (item->GetItemNum() == 0)
		{
			_Hp += 30;
			if (_Hp > 100)
				_Hp = 100;
		}
		else
		{
			if (_Switch == false)
				_Switch = true;
		}
	}
	void Kaho_Cat::alpha()
	{
		int a = cos(_AlphaDegree * PI / 180);
		if (a < 0)
			a *= (-1);
		int alpha = 255 * a;
		_Animator->animationAlpha(alpha);
		if (_AlphaTime > 0.05)
		{
			_AlphaDegree += 90;
			_AlphaTime = 0;
		}
		if (_DamageTime > 2)
		{
			_GetDamage = true;
			_DamageTime = 0;
			_Animator->animationAlpha(255);
		}
	}
	//-------------------------------------------------------------------------------------------------------------------
	//
	//													Events
	// 
	//-------------------------------------------------------------------------------------------------------------------
	void Kaho_Cat::attackStart()
	{
		_ComboCount++;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(1);
	}
	void Kaho_Cat::attackCombo1Start()
	{
		_ComboCount++;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(2);
	}
	void Kaho_Cat::attackCombo2Start()
	{
		_ComboCount++;
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(3);
	}
	void Kaho_Cat::attackAirStart()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		MeleeEffect* melee = object::Instantiate<MeleeEffect>(pos, eLayerType::Attack);
		melee->Dir(_Dir);
		melee->attack(1);
	}
	void Kaho_Cat::attackComplete()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		if (_Combo && _Rigidbody->GetGround()==true)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Attack_2_Right", false);
			else
				_Animator->Play(L"Cat_Attack_2_Left", false);
		}
		else
		{
			_ComboCount = 0;
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
		_Combo = false;
	}
	void Kaho_Cat::attackCombo1Complete()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		if (_Combo)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Attack_3_Right", false);
			else
				_Animator->Play(L"Cat_Attack_3_Left", false);
		}
		else
		{
			_ComboCount = 0;
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
		_Combo = false;
	}
	void Kaho_Cat::attackCombo2Complete()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		_Combo=false;
		_ComboCount = 0;
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
			animationCtrl();
		}
	}
	void Kaho_Cat::dashComplete()
	{
		if (_Dir == eDir::R)
			_Animator->Play(L"Cat_PostDash_Right", false);
		else
			_Animator->Play(L"Cat_PostDash_Left", false);
	}
	void Kaho_Cat::postDashComplete()
	{
		_MoveSpeed = 300.0f;
		_Dashtime = 0.0f;
		_PlayerStatus = ePlayerStatus::Fall;
		animationCtrl();
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
	void Kaho_Cat::afterUseItem()
	{
		if (_Dir == eDir::R)
			_Animator->Play(L"Cat_to_Idle_Right", false);
		else
			_Animator->Play(L"Cat_to_Idle_Left", false);
		_PlayerStatus = ePlayerStatus::Idle;
	}
	void Kaho_Cat::afterDeath()
	{
		_Death = false;
		_Hp = 100;
		Transform* tr = GetComponent<Transform>();
		tr->Pos(_RevivalPos);
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
			if (_Rigidbody->GetGround() == true)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Attack_1_Right", false);
				else
					_Animator->Play(L"Cat_Attack_1_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Attack_1_Right", false);
				else
					_Animator->Play(L"Cat_Attack_1_Left", false);
			}
			break;
		case ePlayerStatus::Roll:
			if (_Rigidbody->GetGround()==true)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Roll_Right", false);
				else
					_Animator->Play(L"Cat_Roll_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Dash_Right", false);
				else
					_Animator->Play(L"Cat_Dash_Left", false);
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
			break;
		case ePlayerStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Hurt_Right", false);
			else
				_Animator->Play(L"Cat_Hurt_Left", false);
			break;
		case ePlayerStatus::UseItem:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_UseItem_Right", false);
			else
				_Animator->Play(L"Cat_UseItem_Left", false);
			break;
		case ePlayerStatus::Death:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cat_Death_Right", false);
			else
				_Animator->Play(L"Cat_Death_Left", false);
			break;
		default:
			break;
		}
	}
}