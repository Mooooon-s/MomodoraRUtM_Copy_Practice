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
		: _status(eStatus::Idle)
		, _Time(0)
		, _Idx(0)
	{
	}
	Momodora::~Momodora()
	{
	}
	void Momodora::Initialize()
	{
		Image* _Image =Resources::Load<Image>(L"Momodora",L"..\\Resources\\Momo.bmp");
		Animator* animator = AddComponent<Animator>();
		//Right
		animator->CreateAnimation(L"Idle_Right",_Image,Vector2::Zero,10,12,6,Vector2::Zero,0.1);
		animator->CreateAnimation(L"Run_Right", _Image, Vector2(0, 48), 10, 12, 8, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"Start_Run_Right", _Image, Vector2(0, (48 * 2)), 10, 12, 2, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"End_Run_Right", _Image, Vector2(0, (48 * 3)), 10, 12, 6, Vector2::Zero, 0.1);
		//Left
		animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, (48 * 4)), 10, 12, 6, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"Run_Left", _Image, Vector2(0, (48 * 5)), 10, 12, 8, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"Start_Run_Left", _Image, Vector2(0, (48 * 6)), 10, 12, 2, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"End_Run_Left", _Image, Vector2(0, (48 * 7)), 10, 12, 6, Vector2::Zero, 0.1);
		//Crouch
		animator->CreateAnimation(L"Crouch_Right", _Image, Vector2(0, (48 * 8)), 10, 12, 4, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"Crouch_Left", _Image, Vector2(0, (48 * 9)), 10, 12, 4, Vector2::Zero, 0.1);

		animator->Play(L"Idle_Right", true);
		
		GameObject::Initialize();
	}
	void Momodora::Update()
	{
		GameObject::Update();
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();

		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyState(eKeyCode::A)==eKeyState::Pressed)
		{
			_status = eStatus::Move;
			animator->Play(L"Run_Left", true);
			pos.x -= 100.0f* Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Down)
		{
			animator->Play(L"Start_Run_Left", true);
		}
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Up)
		{
			//animator->Play(L"End_Run_Right", true);
			animator->Play(L"Idle_Left", true);
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			animator->Play(L"Run_Right", true);
			_status = eStatus::Move;
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Down)
		{
			animator->Play(L"Start_Run_Right", true);
		}
		if(Input::GetKeyState(eKeyCode::D)==eKeyState::Up)
		{
			//animator->Play(L"End_Run_Right", true);
			animator->Play(L"Idle_Right", true);
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			_status = eStatus::Move;
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Down)
		{
			_status = eStatus::Move;
			animator->Play(L"Crouch_Right", false);
			//pos.y += 100.0f * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Up)
		{
			animator->Reset();
			animator->Play(L"Idle_Right", true);
		}
		tr->Pos(pos);
	}

	void Momodora::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Momodora::Release()
	{
		GameObject::Release();
	}
}