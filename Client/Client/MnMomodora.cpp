#include "MnMomodora.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnTime.h"
#include "MnCollider.h"

namespace Mn
{
	Momodora::Momodora()
		: _Status(eStatus::Idle)
		, _animator(nullptr)
		, _Time(0)
		, _Idx(0)
		,_IsJumped(false)
		,_bDoubleJump(true)
		,_Dir(eDir::Right)
		,_col(24)
		,_row(44)
	{
	}
	Momodora::~Momodora()
	{
	}
	void Momodora::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(400.0f, 400.0f));

		Collider* collider = AddComponent<Collider>();
		collider->Center(Vector2(0.0f,0.0f));

		Image* _Image =Resources::Load<Image>(L"Momodora",L"..\\Resources\\Kaho_Human.bmp");
		_animator = AddComponent<Animator>();

		//Move Right
		_animator->CreateAnimation(L"Idle_Right",_Image,Vector2::Zero,_col,_row,6,Vector2::Zero,0.1);
		_animator->CreateAnimation(L"Run_Right", _Image, Vector2(0, 48), _col, _row, 8, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Start_Run_Right", _Image, Vector2(0, (48 * 2)), _col, _row, 2, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"End_Run_Right", _Image, Vector2(0, (48 * 3)), _col, _row, 6, Vector2::Zero, 0.1);
		//Move Left
		_animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, (48 * 4)), _col, _row, 6, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Run_Left", _Image, Vector2(0, (48 * 5)), _col, _row, 8, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Start_Run_Left", _Image, Vector2(0, (48 * 6)), _col, _row, 2, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"End_Run_Left", _Image, Vector2(0, (48 * 7)), _col, _row, 6, Vector2::Zero, 0.1);
		//Hurt
		_animator->CreateAnimation(L"Hurt_Right", _Image, Vector2(96, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Hurt_Left", _Image, Vector2(142, (48 * 2)), _col, _row, 1, Vector2::Zero, 0.1);
		//Crouch
		_animator->CreateAnimation(L"Crouch_Right", _Image, Vector2(0, (48 * 8)), _col, _row, 4, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Crouch_Left", _Image, Vector2(0, (48 * 9)), _col, _row, 4, Vector2::Zero, 0.1);
		//Rise
		_animator->CreateAnimation(L"Rise_Right", _Image, Vector2(0, (48 * 10)), _col, _row, 2, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Rise_Left", _Image, Vector2(0, (48 * 11)), _col, _row, 2, Vector2::Zero, 0.1);
		//Jump
		_animator->CreateAnimation(L"Jump_Right", _Image, Vector2(0, (48 * 12)), _col, _row, 3, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Jump_Left", _Image, Vector2(0, (48 * 13)), _col, _row, 3, Vector2::Zero, 0.1);
		//Fall
		_animator->CreateAnimation(L"Fall_Right", _Image, Vector2(0, (48 * 14)), _col, _row, 5, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Fall_Left", _Image, Vector2(0, (48 * 15)), _col, _row, 5, Vector2::Zero, 0.1);
		//Rolling
		_animator->CreateAnimation(L"Roll_Right", _Image, Vector2(0, (48 * 16)), _col, _row, 8, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Roll_Left", _Image, Vector2(0, (48 * 17)), _col, _row, 8, Vector2::Zero, 0.1);
		//Range Attack
		_animator->CreateAnimation(L"Range_Attack_Right", _Image, Vector2(0, (48 * 18)), _col, _row, 6, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Range_Attack_Left", _Image, Vector2(0, (48 * 19)), _col, _row, 6, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Air_Range_Attack_Right", _Image, Vector2(288, (48 * 18)), _col, _row, 6, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Air_Range_Attack_Left", _Image, Vector2(288, (48 * 19)), _col, _row, 6, Vector2::Zero, 0.1);
		//Melee Attack_1
		_animator->CreateAnimation(L"Melee_Attack_1_Right", _Image, Vector2(0, (48 * 20)), _col, _row, 7, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Melee_Attack_1_Left", _Image, Vector2(0, (48 * 21)), _col, _row, 7, Vector2::Zero, 0.1);
		//Air_Melee_Attack_1
		_animator->CreateAnimation(L"Air_Melee_Attack_Right", _Image, Vector2(0, (48 * 22)), _col, _row, 7, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Air_Melee_Attack_Left", _Image, Vector2(0, (48 * 23)), _col, _row, 7, Vector2::Zero, 0.1);
		//Melee_Attack_2
		_animator->CreateAnimation(L"Melee_Attack_2_Right", _Image, Vector2(0, (48 * 24)), _col, _row, 7, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Melee_Attack_2_Left", _Image, Vector2(0, (48 * 25)), _col, _row, 7, Vector2::Zero, 0.1);
		//Melee_Attack_3
		_animator->CreateAnimation(L"Melee_Attack_3_Right", _Image, Vector2(0, (48 * 26)), _col, _row, 11, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Melee_Attack_3_Left", _Image, Vector2(0, (48 * 27)), _col, _row, 11, Vector2::Zero, 0.1);
		//Leder_Up
		_animator->CreateAnimation(L"Leader_Up", _Image, Vector2(0, (48 * 28)), _col, _row, 6, Vector2::Zero, 0.1);
		//Leder_Down
		_animator->CreateAnimation(L"Leader_Down", _Image, Vector2(0, (48 * 29)), _col, _row, 3, Vector2::Zero, 0.1);
		//Use_Item
		_animator->CreateAnimation(L"Use_Item_Right", _Image, Vector2(0, (48 * 30)), _col, _row, 11, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Use_Iteem_Left", _Image, Vector2(0, (48 * 31)), _col, _row, 11, Vector2::Zero, 0.1);
		//Dash
		_animator->CreateAnimation(L"Dash_Right", _Image, Vector2(192, (48 * 4)), _col, _row, 1, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Dash_Left", _Image, Vector2(240, (48 * 4)), _col, _row, 1, Vector2::Zero, 0.1);
		//preDash
		_animator->CreateAnimation(L"PreDash_Right", _Image, Vector2(0, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"PostDash_Right", _Image, Vector2(144, (48 * 32)), _col, _row, 3, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"PreDash_Left", _Image, Vector2(0, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"PostDash_Left", _Image, Vector2(144, (48 * 33)), _col, _row, 3, Vector2::Zero, 0.1);
		//soft_Landing
		_animator->CreateAnimation(L"soft_Landing_Right", _Image, Vector2(0, (48 * 34)), _col, _row, 11, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"soft_Landing_Left", _Image, Vector2(0, (48 * 35)), _col, _row, 11, Vector2::Zero, 0.1);
		//Hard_Landing
		_animator->CreateAnimation(L"Hard_Landing_Right", _Image, Vector2(0, (48 * 36)), _col, _row, 11, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Hard_Landing_Left", _Image, Vector2(0, (48 * 37)), _col, _row, 11, Vector2::Zero, 0.1);
		//Look_Around
		_animator->CreateAnimation(L"Look_Around_Right", _Image, Vector2(0, (48 * 38)), _col, _row, 11, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Look_Around_Left", _Image, Vector2(0, (48 * 39)), _col, _row, 11, Vector2::Zero, 0.1);
		//Spin
		_animator->CreateAnimation(L"Spin_Right", _Image, Vector2(0, (48 * 40)), _col, _row, 11, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Spin_Left", _Image, Vector2(0, (48 * 41)), _col, _row, 11, Vector2::Zero, 0.1);

		//Death
		_animator->CreateAnimation(L"Death_Right", _Image, Vector2(0, (48 * 42)), _col, _row, 24, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Death_Left", _Image, Vector2(0, (48 * 43)), _col, _row, 24, Vector2::Zero, 0.1);

		_animator->Play(L"Idle_Right", true);
		
		GameObject::Initialize();
	}
	void Momodora::Update()
	{
		GameObject::Update();
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();

		_animator = GetComponent<Animator>();

		switch (_Status)
		{
		case eStatus::Idle:
			idle();
			break;
		case eStatus::Move:
			move();
			break;
		case eStatus::Rolling:
			rolling();
			break;
		case eStatus::Crouch:
			crouch();
			break;
		case eStatus::Jump:
			jump();
			break;
		case eStatus::Melee:
			meleeAttack();
			break;
		case eStatus::Range:
			rangeAttack();
			break;
		case eStatus::Climb:
			climb();
			break;
		case eStatus::UseItem:
			useItem();
			break;
		case eStatus::Hurt:
			hurt();
			break;
		case eStatus::GetItem:
			getItem();
			break;
		case eStatus::Death:
			death();
			break;
		default:
			break;
		}

	}

	void Momodora::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Momodora::Release()
	{
		GameObject::Release();
	}

	void Momodora::playAnimationDirection()
	{
		switch (_Status)
		{
		case eStatus::Idle:
			if (_Dir == eDir::Left)
				_animator->Play(L"Idle_Left", true);
			else
				_animator->Play(L"Idle_Right", true);
			break;
		case eStatus::Move:
			if (_Dir == eDir::Left)
				_animator->Play(L"Run_Left", true);
			else
				_animator->Play(L"Run_Right", true);
			break;
		case eStatus::Rolling:
			if (_Dir == eDir::Left)
				_animator->Play(L"Roll_Left", false);
			else
				_animator->Play(L"Roll_Right", false);
			break;
		case eStatus::Crouch:
			if (_Dir == eDir::Left)
				_animator->Play(L"Crouch_Left", false);
			else
				_animator->Play(L"Crouch_Right", false);
			break;
		case eStatus::Jump:
			
			if (_Dir == eDir::Left)
				_animator->Play(L"Jump_Left", false);
			else
				_animator->Play(L"Jump_Right", false);
			break;
		case eStatus::Melee:
			if (_IsJumped)
			{
				if (_Dir == eDir::Left)
					_animator->Play(L"Air_Melee_Attack_Left", false);
				else
					_animator->Play(L"Air_Melee_Attack_Right", false);
				_IsJumped = false;
			}
			else
			{
				if (_Dir == eDir::Left)
					_animator->Play(L"Melee_Attack_1_Left", false);
				else
					_animator->Play(L"Melee_Attack_1_Right", false);
			}
			break;
		case eStatus::Range:
			if (_IsJumped)
			{
				if (_Dir == eDir::Left)
					_animator->Play(L"Air_Range_Attack_Left", false);
				else
					_animator->Play(L"Air_Range_Attack_Right", false);
			}
			else
			{
				if (_Dir == eDir::Left)
					_animator->Play(L"Range_Attack_Left", false);
				else
					_animator->Play(L"Range_Attack_Right", false);
			}
			break;
		case eStatus::UseItem:
			if (_Dir == eDir::Left)
				_animator->Play(L"Use_Item_Left", false);
			else
				_animator->Play(L"Use_Item_Right", false);
			break;
		case eStatus::Hurt:
			if (_Dir == eDir::Left)
				_animator->Play(L"Hurt_Left", false);
			else
				_animator->Play(L"Hurt_Right", false);
			break;
		case eStatus::GetItem:
			if (_Dir == eDir::Left)
				_animator->Play(L"Spin_Left", false);
			else
				_animator->Play(L"Spin_Right", false);
			break;
		case eStatus::Death:
			if (_Dir == eDir::Left)
				_animator->Play(L"Death_Left", false);
			else
				_animator->Play(L"Death_Right", false);
			break;
		default:
			break;
		}
	}

	void Momodora::move()
	{
		//Run_to_Idle
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}

		//Run_to_Melee
		if (Input::GetKey(eKeyCode::S))
		{
			_Status = eStatus::Melee;
			playAnimationDirection();
		}
		//Run_to_Range
		if (Input::GetKey(eKeyCode::D))
		{
			_Status = eStatus::Range;
			playAnimationDirection();

		}
		//Run_to_Crouch
		if (Input::GetKey(eKeyCode::Down))
		{
			_Status = eStatus::Crouch;
			playAnimationDirection();
		}
		//Run_to_jump
		if (Input::GetKey(eKeyCode::A))
		{
			_Status = eStatus::Jump;
			playAnimationDirection();
		}
		//Run_to_Roll
		if (Input::GetKey(eKeyCode::Q))
		{
			_Status = eStatus::Rolling;
			playAnimationDirection();
		}


		//Move pos
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();

		if (Input::GetKey(eKeyCode::Left))
		{
			_Dir = eDir::Left;
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Dir = eDir::Right;
		}

		if(_Dir==eDir::Left)
			pos.x -= 100.0f * Time::DeltaTime();
		else
			pos.x += 100.0f * Time::DeltaTime();
		
		playAnimationDirection();



		tr->Pos(pos);
	}

	void Momodora::idle()
	{
		if (Input::GetKey(eKeyCode::Left))
		{
			_Status = eStatus::Move;
			_Dir = eDir::Left;
			playAnimationDirection();
		}
		if (Input::GetKey(eKeyCode::Right))
		{
			_Status = eStatus::Move;
			_Dir = eDir::Right;
			playAnimationDirection();
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_Status = eStatus::Crouch;
			playAnimationDirection();
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_Status = eStatus::Rolling;
			playAnimationDirection();
		}
		//Jump
		if (Input::GetKeyDown(eKeyCode::A))
		{
			_Status = eStatus::Jump;
			playAnimationDirection();
		}
		//Melee Attack
		if (Input::GetKeyDown(eKeyCode::S))
		{
			_Status = eStatus::Melee;
			playAnimationDirection();
		}
		//Range Attack
		if (Input::GetKeyDown(eKeyCode::D))
		{
			_Status = eStatus::Range;
			playAnimationDirection();
		}
		//Menu
		if (Input::GetKeyDown(eKeyCode::Shift))
		{
			//test
			_animator->Play(L"Melee_Attack_2_Right", false);
		}
		//Map
		if (Input::GetKeyDown(eKeyCode::Tab))
		{
			//test
			_animator->Play(L"Melee_Attack_3_Right", false);
		}
		//Climb_Up
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			_Status = eStatus::Climb;
			_animator->Play(L"Leader_Up", true);
		}
		//Climb_down
		if (Input::GetKeyDown(eKeyCode::O))
		{
			_Status = eStatus::Climb;
			_animator->Play(L"Leader_Down", true);
		}
		//UseItem
		if (Input::GetKeyDown(eKeyCode::W))
		{
			_Status = eStatus::UseItem;
			playAnimationDirection();
		}
		if (Input::GetKeyDown(eKeyCode::L))
		{
			_Status = eStatus::Hurt;
			playAnimationDirection();
		}
		//Get_Item
		if (Input::GetKeyDown(eKeyCode::P))
		{
			_Status = eStatus::GetItem;
			playAnimationDirection();
		}
		if (Input::GetKeyDown(eKeyCode::U))
		{
			_Status = eStatus::Death;
			playAnimationDirection();
		}
	}

	void Momodora::jump()
	{
		if (Input::GetKeyUp(eKeyCode::A))
		{
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			_IsJumped = true;
			_Status = eStatus::Range;
			playAnimationDirection();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			_IsJumped=true;
			_Status = eStatus::Melee;
			playAnimationDirection();
		}
	}

	void Momodora::hurt()
	{
		if (Input::GetKeyUp(eKeyCode::L))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::climb()
	{
		if (Input::GetKeyUp(eKeyCode::Up)
			|| Input::GetKeyUp(eKeyCode::O))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::death()
	{
		//GameOver
		if (Input::GetKeyUp(eKeyCode::U))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::crouch()
	{
		if (Input::GetKey(eKeyCode::D))
		{
			//_Status = eStatus::Range;
			//playAnimationDirection();
		}
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::rolling()
	{
		if (Input::GetKeyUp(eKeyCode::Q))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::getItem()
	{
		if (Input::GetKeyUp(eKeyCode::P))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::meleeAttack()
	{
		if (Input::GetKeyUp(eKeyCode::S))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}

	}

	void Momodora::rangeAttack()
	{
		if (Input::GetKeyUp(eKeyCode::D))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

	void Momodora::useItem()
	{
		if (Input::GetKeyUp(eKeyCode::W))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
	}

}



