#include "MnMomodora.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnTime.h"

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
		,_col(11)
		,_row(28)
	{
	}
	Momodora::~Momodora()
	{
	}
	void Momodora::Initialize()
	{
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
			if (_Dir == eDir::Left)
				_animator->Play(L"Range_Attack_Left", false);
			else
				_animator->Play(L"Range_Attack_Right", false);
			break;
		case eStatus::Climb:
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
		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();

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
	}

	void Momodora::jump()
	{
		/*Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		if (pos.y <= tr->Pos().y)
		{
			if (_Dir == eDir::Left)
				_animator->Play(L"Fall_Left", false);
			else
				_animator->Play(L"Fall_Right", false);
		}
		if (Input::GetKeyDown(eKeyCode::A) && _bDoubleJump == true)
		{
			if (_Dir == eDir::Left)
				_animator->Play(L"Jump_Left", false);
			else
				_animator->Play(L"Jump_Right", false);

			_bDoubleJump = false;
		}*/

		if (Input::GetKeyUp(eKeyCode::A))
		{
			_Status = eStatus::Idle;
			playAnimationDirection();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			_IsJumped=true;
			_Status = eStatus::Melee;
			playAnimationDirection();
		}
	}

	void Momodora::crouch()
	{
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

}



