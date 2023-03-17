#include "MnKaho_Human.h"
#include "MnResources.h"
#include "MnInput.h"
#include "MnTime.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnSceneManager.h"
#include "MnScene.h"
#include "MnArrow.h"
#include "MnObject.h"

namespace Mn
{
	Kaho_Human::Kaho_Human()
		:_PlayerStatus(ePlayerStatus::Idle)
		,_Animator(nullptr)
		, _Image(nullptr)
		,_Combo(false)
		, _IsCrouch(false)
		, _IsJump(false)
		,_IsActive(true)
		,_Dir(eDir::R)
		, _col(24)
		, _row(44)
	{
	}
	Kaho_Human::~Kaho_Human()
	{
	}
	void Kaho_Human::Initialize()
	{
		Transform* tr = GetComponent<Transform>();

		//Collider* collider = AddComponent<Collider>();
		//collider->Center(Vector2(-12.0f * 3, -40.0f * 3));
		//collider->Size(Vector2(24.0f * 3, 40.0f * 3));

		Image* _Image = Resources::Load<Image>(L"Kaho", L"..\\Resources\\Kaho_Human.bmp");
		_Animator = AddComponent<Animator>();
		//-------------------------------------------------------------------------------------------------------------
		//												
		//												Kaho_Human Animation
		// 
		// ------------------------------------------------------------------------------------------------------------
		//Move Right
		_Animator->CreateAnimation(L"Idle_Right", _Image, Vector2::Zero, _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Run_Right", _Image, Vector2(0, 48), _col, _row, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Start_Run_Right", _Image, Vector2(0, (48 * 2)), _col, _row, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"End_Run_Right", _Image, Vector2(0, (48 * 3)), _col, _row, 6, Vector2::Zero, 0.08);
		//Move Left
		_Animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, (48 * 4)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Run_Left", _Image, Vector2(0, (48 * 5)), _col, _row, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Start_Run_Left", _Image, Vector2(0, (48 * 6)), _col, _row, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"End_Run_Left", _Image, Vector2(0, (48 * 7)), _col, _row, 6, Vector2::Zero, 0.08);
		//Hurt
		_Animator->CreateAnimation(L"Hurt_Right", _Image, Vector2(96, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hurt_Left", _Image, Vector2(142, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.08);
		//Crouch
		_Animator->CreateAnimation(L"Crouch_Right", _Image, Vector2(0, (48 * 8)), _col, _row, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Crouch_Left", _Image, Vector2(0, (48 * 9)), _col, _row, 4, Vector2::Zero, 0.08);
		//Rise
		_Animator->CreateAnimation(L"Rise_Right", _Image, Vector2(0, (48 * 10)), _col, _row, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Rise_Left", _Image, Vector2(0, (48 * 11)), _col, _row, 2, Vector2::Zero, 0.08);
		//Jump
		_Animator->CreateAnimation(L"Jump_Right", _Image, Vector2(0, (48 * 12)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Jump_Left", _Image, Vector2(0, (48 * 13)), _col, _row, 3, Vector2::Zero, 0.08);
		//Fall
		_Animator->CreateAnimation(L"Fall_Right", _Image, Vector2(0, (48 * 14)), _col, _row, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fall_Left", _Image, Vector2(0, (48 * 15)), _col, _row, 5, Vector2::Zero, 0.08);
		//Rolling
		_Animator->CreateAnimation(L"Roll_Right", _Image, Vector2(0, (48 * 16)), _col, _row, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Roll_Left", _Image, Vector2(0, (48 * 17)), _col, _row, 8, Vector2::Zero, 0.08);
		//Range Attack
		_Animator->CreateAnimation(L"Range_Attack_Right", _Image, Vector2(0, (48 * 18)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Range_Attack_Left", _Image, Vector2(0, (48 * 19)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Range_Attack_Right", _Image, Vector2(288, (48 * 18)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Range_Attack_Left", _Image, Vector2(288, (48 * 19)), _col, _row, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Crouch_Range_Attack_Right", _Image, Vector2(576, (48 * 18)), _col, _row, 6, Vector2(0.0f, 12.0f), 0.08);
		_Animator->CreateAnimation(L"Crouch_Range_Attack_Left", _Image, Vector2(576, (48 * 19)), _col, _row, 6, Vector2(0.0f, 12.0f), 0.08);
		//Melee Attack_1
		_Animator->CreateAnimation(L"Melee_Attack_1_Right", _Image, Vector2(0, (48 * 20)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Melee_Attack_1_Left", _Image, Vector2(0, (48 * 21)), _col, _row, 7, Vector2::Zero, 0.08);
		//Air_Melee_Attack_1
		_Animator->CreateAnimation(L"Air_Melee_Attack_Right", _Image, Vector2(0, (48 * 22)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Air_Melee_Attack_Left", _Image, Vector2(0, (48 * 23)), _col, _row, 7, Vector2::Zero, 0.08);

		//Melee_Attack_2
		_Animator->CreateAnimation(L"Melee_Attack_2_Right", _Image, Vector2(0, (48 * 24)), _col, _row, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Melee_Attack_2_Left", _Image, Vector2(0, (48 * 25)), _col, _row, 7, Vector2::Zero, 0.08);
		//Melee_Attack_3
		_Animator->CreateAnimation(L"Melee_Attack_3_Right", _Image, Vector2(0, (48 * 26)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Melee_Attack_3_Left", _Image, Vector2(0, (48 * 27)), _col, _row, 11, Vector2::Zero, 0.08);
		//Leder_Up
		_Animator->CreateAnimation(L"Leader_Up", _Image, Vector2(0, (48 * 28)), _col, _row, 6, Vector2::Zero, 0.08);
		//Leder_Down
		_Animator->CreateAnimation(L"Leader_Down", _Image, Vector2(0, (48 * 29)), _col, _row, 3, Vector2::Zero, 0.08);
		//Use_Item
		_Animator->CreateAnimation(L"Use_Item_Right", _Image, Vector2(0, (48 * 30)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Use_Item_Left", _Image, Vector2(0, (48 * 31)), _col, _row, 11, Vector2::Zero, 0.08);
		//Dash
		_Animator->CreateAnimation(L"Dash_Right", _Image, Vector2(192, (48 * 4)), _col, _row, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Dash_Left", _Image, Vector2(240, (48 * 4)), _col, _row, 1, Vector2::Zero, 0.08);
		//preDash
		_Animator->CreateAnimation(L"PreDash_Right", _Image, Vector2(0, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PostDash_Right", _Image, Vector2(144, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PreDash_Left", _Image, Vector2(0, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"PostDash_Left", _Image, Vector2(144, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.08);
		//soft_Landing
		_Animator->CreateAnimation(L"soft_Landing_Right", _Image, Vector2(0, (48 * 34)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"soft_Landing_Left", _Image, Vector2(0, (48 * 35)), _col, _row, 11, Vector2::Zero, 0.08);
		//Hard_Landing
		_Animator->CreateAnimation(L"Hard_Landing_Right", _Image, Vector2(0, (48 * 36)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hard_Landing_Left", _Image, Vector2(0, (48 * 37)), _col, _row, 11, Vector2::Zero, 0.08);
		//Look_Around
		_Animator->CreateAnimation(L"Look_Around_Right", _Image, Vector2(0, (48 * 38)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Look_Around_Left", _Image, Vector2(0, (48 * 39)), _col, _row, 11, Vector2::Zero, 0.08);
		//Spin
		_Animator->CreateAnimation(L"Spin_Right", _Image, Vector2(0, (48 * 40)), _col, _row, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Spin_Left", _Image, Vector2(0, (48 * 41)), _col, _row, 11, Vector2::Zero, 0.08);

		//Death
		_Animator->CreateAnimation(L"Death_Right", _Image, Vector2(0, (48 * 42)), _col, _row, 24, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Death_Left", _Image, Vector2(0, (48 * 43)), _col, _row, 24, Vector2::Zero, 0.08);

		//-------------------------------------------------------------------------------------------------------------------
		//
		//													Events
		// 
		//-------------------------------------------------------------------------------------------------------------------
		//ComboAttack
		_Animator->GetCompleteEvent(L"Melee_Attack_1_Right") = std::bind(&Kaho_Human::attackComplete, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_1_Left") = std::bind(&Kaho_Human::attackComplete, this);

		_Animator->GetCompleteEvent(L"Melee_Attack_2_Right") = std::bind(&Kaho_Human::attackCombo1Complete, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_2_Left") = std::bind(&Kaho_Human::attackCombo1Complete, this);

		_Animator->GetCompleteEvent(L"Melee_Attack_3_Right") = std::bind(&Kaho_Human::attackCombo2Complete, this);
		_Animator->GetCompleteEvent(L"Melee_Attack_3_Left") = std::bind(&Kaho_Human::attackCombo2Complete, this);

		_Animator->GetStartEvent(L"Range_Attack_Right") = std::bind(&Kaho_Human::beforeRange, this);
		_Animator->GetCompleteEvent(L"Range_Attack_Right") = std::bind(&Kaho_Human::afterRange, this);

		_Animator->GetStartEvent(L"Range_Attack_Left") = std::bind(&Kaho_Human::beforeRange, this);
		_Animator->GetCompleteEvent(L"Range_Attack_Left") = std::bind(&Kaho_Human::afterRange, this);

		_Animator->GetCompleteEvent(L"Air_Melee_Attack_Right") = std::bind(&Kaho_Human::airAttackComplete, this);
		_Animator->GetCompleteEvent(L"Air_Melee_Attack_Left") = std::bind(&Kaho_Human::airAttackComplete, this);


		_Animator->GetStartEvent(L"Crouch_Range_Attack_Right") = std::bind(&Kaho_Human::CrouchRangeStart, this);
		_Animator->GetStartEvent(L"Crouch_Range_Attack_Left") = std::bind(&Kaho_Human::CrouchRangeStart, this);

		_Animator->GetCompleteEvent(L"Crouch_Range_Attack_Right") = std::bind(&Kaho_Human::CrouchRangeComplete, this);
		_Animator->GetCompleteEvent(L"Crouch_Range_Attack_Left") = std::bind(&Kaho_Human::CrouchRangeComplete, this);

		_Animator->GetCompleteEvent(L"Roll_Right") = std::bind(&Kaho_Human::afterRoll, this);
		_Animator->GetCompleteEvent(L"Roll_Left") = std::bind(&Kaho_Human::afterRoll, this);


		_Animator->GetCompleteEvent(L"Use_Item_Right") = std::bind(&Kaho_Human::afterUseItem, this);
		_Animator->GetCompleteEvent(L"Use_Item_Left") = std::bind(&Kaho_Human::afterUseItem, this);

		_Animator->GetCompleteEvent(L"Rise_Right") = std::bind(&Kaho_Human::riseUp, this);
		_Animator->GetCompleteEvent(L"Rise_Left") = std::bind(&Kaho_Human::riseUp, this);

		_Animator->GetCompleteEvent(L"End_Run_Right") = std::bind(&Kaho_Human::EndRun, this);
		_Animator->GetCompleteEvent(L"End_Run_Left") = std::bind(&Kaho_Human::EndRun, this);

		_Animator->Play(L"Idle_Right", true);
		GameObject::Initialize();
	}
	void Kaho_Human::Update()
	{
		if (_IsActive)
		{
			Transform* tr = GetComponent<Transform>();
			_pos = tr->Pos();

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
			case ePlayerStatus::Shoot:
				shoot();
				break;
			case ePlayerStatus::Crouch:
				crouch();
				break;
			case ePlayerStatus::Jump:
				jump();
				break;
			case ePlayerStatus::Roll:
				roll();
				break;
			case ePlayerStatus::UseItem:
				useItem();
				break;
			default:
				break;
			}

			tr->Pos(_pos);

			GameObject::Update();
		}
	}
	void Kaho_Human::Render(HDC hdc)
	{
		if(_IsActive)
			GameObject::Render(hdc);
	}
	void Kaho_Human::Release()
	{
		GameObject::Release();
	}

	//status
	void Kaho_Human::animationCtrl()
	{
		switch (_PlayerStatus)
		{
		case ePlayerStatus::Idle:
			if (_Dir == eDir::R)
			{
				_Animator->Play(L"Idle_Right", true);
			}
			else
				_Animator->Play(L"Idle_Left", true);
			break;
		case ePlayerStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Run_Right", true);
			else
				_Animator->Play(L"Run_Left", true);
			break;
		case ePlayerStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Melee_Attack_1_Right", false);
			else
				_Animator->Play(L"Melee_Attack_1_Left", false);
			break;
		case ePlayerStatus::Shoot:
			if (!_IsCrouch)
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Range_Attack_Right", false);
				else
					_Animator->Play(L"Range_Attack_Left", false);
			}
			else
			{
				if (_Dir == eDir::R)
					_Animator->Play(L"Crouch_Range_Attack_Right", false);
				else
					_Animator->Play(L"Crouch_Range_Attack_Left", false);
			}
			break;
		case ePlayerStatus::Crouch:
			if (_Dir == eDir::R)
				_Animator->Play(L"Crouch_Right", false);
			else
				_Animator->Play(L"Crouch_Left", false);
			break;
		case ePlayerStatus::Jump:
			if (_Dir == eDir::R)
				_Animator->Play(L"Jump_Right", false);
			else
				_Animator->Play(L"Jump_Left", false);
			break;
		case ePlayerStatus::Roll:
			if (_Dir == eDir::R)
				_Animator->Play(L"Roll_Right", false);
			else
				_Animator->Play(L"Roll_Left", false);
			break;
		case ePlayerStatus::UseItem:
			if (_Dir == eDir::R)
				_Animator->Play(L"Use_Item_Right", false);
			else
				_Animator->Play(L"Use_Item_Left", false);
			break;
		default:
			break;
		}
	}
	void Kaho_Human::idle()
	{
		if (Input::GetKeyUp(eKeyCode::D))
		{
			_PlayerStatus = ePlayerStatus::Shoot;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}
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
			_IsCrouch = true;
			_PlayerStatus = ePlayerStatus::Crouch;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			//_IsJump = true;
			_PlayerStatus = ePlayerStatus::Jump;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_PlayerStatus = ePlayerStatus::Roll;
			animationCtrl();
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_PlayerStatus = ePlayerStatus::UseItem;
			animationCtrl();
		}
	}
	void Kaho_Human::move()
	{
		//Run_to_Idle
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			_PlayerStatus = ePlayerStatus::Idle;
			if (_Dir == eDir::R)
				_Animator->Play(L"End_Run_Right", false);
			else
				_Animator->Play(L"End_Run_Left", false);
		}
		//Move pos
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
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_PlayerStatus = ePlayerStatus::UseItem;
			animationCtrl();
		}

		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
			if (Input::GetKeyDown(eKeyCode::Right))
			{
				_Animator->Play(L"Idle_Left", true);
			}
			else
				animationCtrl();
		}
		else if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
			if (Input::GetKeyDown(eKeyCode::Left))
			{
				_Animator->Play(L"Idle_Right", true);
			}
			else
				animationCtrl();
		}
		if (_Dir == eDir::L)
			_pos.x -= 100.0f * Time::DeltaTime();
		else
			_pos.x += 100.0f * Time::DeltaTime();
	}
	void Kaho_Human::attack()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::L;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::R;
		}
		if (_Animator->GetActiveAnim()->IsComplete()==false)
		{
			if (Input::GetKeyDown(eKeyCode::S))
				_Combo = true;
		}
	}
	void Kaho_Human::shoot()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			_PlayerStatus = ePlayerStatus::Idle;
		}

		if (Input::GetKey(eKeyCode::Down))
		{
			_PlayerStatus = ePlayerStatus::Crouch;
		}
	}
	void Kaho_Human::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Rise_Right", false);
			else
				_Animator->Play(L"Rise_Left", false);
		}

		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_PlayerStatus=ePlayerStatus::Crouch;
			animationCtrl();
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			_PlayerStatus = ePlayerStatus::Attack;
			animationCtrl();
		}


		if (Input::GetKeyDown(eKeyCode::D))
		{
			_PlayerStatus = ePlayerStatus::Shoot;
			animationCtrl();
		}
	}
	void Kaho_Human::jump()
	{
		if (Input::GetKeyUp(eKeyCode::A))
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Human::roll()
	{
	}
	void Kaho_Human::useItem()
	{
	}

	//Animation Event
	void Kaho_Human::attackComplete()
	{
		if (_Combo == true)
		{
			_Combo = false;
			if (_Dir == eDir::R)
				_Animator->Play(L"Melee_Attack_2_Right", false);
			else
				_Animator->Play(L"Melee_Attack_2_Left", false);
		}
		else
		{
			
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Human::attackCombo1Complete()
	{
		if (_Combo == true)
		{
			_Combo = false;
			if (_Dir == eDir::R)
				_Animator->Play(L"Melee_Attack_3_Right", false);
			else
				_Animator->Play(L"Melee_Attack_3_Left", false);
		}
		else
		{
			_PlayerStatus = ePlayerStatus::Idle;
			animationCtrl();
		}
	}
	void Kaho_Human::attackCombo2Complete()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::airAttackComplete()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}

	void Kaho_Human::CrouchRangeStart()
	{
		Transform* tr = GetComponent<Transform>();
		object::Instantiate<Arrow>(tr->Pos(), eLayerType::Attack);
	}

	void Kaho_Human::CrouchRangeComplete()
	{
		animationCtrl();
	}
	void Kaho_Human::beforeRange()
	{
		Transform* tr = GetComponent<Transform>();
		object::Instantiate<Arrow>(tr->Pos(),eLayerType::Attack);
	}
	void Kaho_Human::afterRange()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::afterRoll()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::afterUseItem()
	{
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::riseUp()
	{
		_IsCrouch = false;
		_PlayerStatus = ePlayerStatus::Idle;
		animationCtrl();
	}
	void Kaho_Human::EndRun()
	{
		animationCtrl();
	}
}