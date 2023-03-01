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
		, _Time(0)
		, _Idx(0)
	{
	}
	Momodora::~Momodora()
	{
	}
	void Momodora::Initialize()
	{
		Image* _Image =Resources::Load<Image>(L"Momodora",L"..\\Resources\\Kaho_Human.bmp");
		_animator = AddComponent<Animator>();
		//Right
		_animator->CreateAnimation(L"Idle_Right",_Image,Vector2::Zero,10,18,6,Vector2::Zero,0.1);
		_animator->CreateAnimation(L"Run_Right", _Image, Vector2(0, 48), 10, 18, 8, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Start_Run_Right", _Image, Vector2(0, (48 * 2)), 10, 18, 2, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"End_Run_Right", _Image, Vector2(0, (48 * 3)), 10, 18, 6, Vector2::Zero, 0.1);
		//Left
		_animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, (48 * 4)), 10, 18, 6, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Run_Left", _Image, Vector2(0, (48 * 5)), 10, 18, 8, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Start_Run_Left", _Image, Vector2(0, (48 * 6)), 10, 18, 2, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"End_Run_Left", _Image, Vector2(0, (48 * 7)), 10, 18, 6, Vector2::Zero, 0.1);
		//Crouch
		_animator->CreateAnimation(L"Crouch_Right", _Image, Vector2(0, (48 * 8)), 10, 18, 4, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Crouch_Left", _Image, Vector2(0, (48 * 9)), 10, 18, 4, Vector2::Zero, 0.1);
		//Rise
		_animator->CreateAnimation(L"Rise_Right", _Image, Vector2(0, (48 * 10)), 10, 18, 2, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Rise_Left", _Image, Vector2(0, (48 * 11)), 10, 18, 2, Vector2::Zero, 0.1);
		//Jump
		_animator->CreateAnimation(L"Jump_Right", _Image, Vector2(0, (48 * 12)), 10, 18, 3, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Jump_Left", _Image, Vector2(0, (48 * 13)), 10, 18, 3, Vector2::Zero, 0.1);
		//Fall
		_animator->CreateAnimation(L"Fall_Right", _Image, Vector2(0, (48 * 14)), 10, 18, 5, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Fall_Left", _Image, Vector2(0, (48 * 15)), 10, 18, 5, Vector2::Zero, 0.1);
		//Rolling
		_animator->CreateAnimation(L"Roll_Right", _Image, Vector2(0, (48 * 16)), 10, 18, 8, Vector2::Zero, 0.1);
		_animator->CreateAnimation(L"Roll_Left", _Image, Vector2(0, (48 * 17)), 10, 18, 8, Vector2::Zero, 0.1);

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
			break;
		case eStatus::Melee:
			break;
		case eStatus::Range:
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

	void Momodora::move()
	{
		if (Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			if (_Dir == eDir::Left)
			{
				_Status = eStatus::Idle;
				_animator->Play(L"Idle_Left", true);
			}
			else
			{
				_Status = eStatus::Idle;
				_animator->Play(L"Idle_Right", true);
			}
		}


		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();

		if (Input::GetKey(eKeyCode::Left))
			pos.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::Right))
			pos.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();
		tr->Pos(pos);
	}

	void Momodora::idle()
	{
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			_Status = eStatus::Move;
			_Dir = eDir::Left;
			_animator->Play(L"Run_Left", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			_Status = eStatus::Move;
			_Dir = eDir::Right;
			_animator->Play(L"Run_Right", true);
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			_Status = eStatus::Crouch;
			if (_Dir == eDir::Left)
				_animator->Play(L"Crouch_Left", false);
			else
				_animator->Play(L"Crouch_Right", false);
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			_Status = eStatus::Rolling;
			if (_Dir == eDir::Left)
				_animator->Play(L"Roll_Left", false);
			else
				_animator->Play(L"Roll_Right", false);
		}
	}

	void Momodora::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			_Status = eStatus::Idle;
			if (_Dir == eDir::Left)
				_animator->Play(L"Idle_Left", true);
			else
				_animator->Play(L"Idle_Right", true);
		}
	}

	void Momodora::rolling()
	{
		if (Input::GetKeyUp(eKeyCode::Q))
		{
			_Status = eStatus::Idle;
			if (_Dir == eDir::Left)
				_animator->Play(L"Idle_Left", true);
			else
				_animator->Play(L"Idle_Right", true);
		}
	}

}



