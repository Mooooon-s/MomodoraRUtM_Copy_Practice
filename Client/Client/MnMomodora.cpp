#include "MnMomodora.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnResources.h"
#include "MnTransform.h"



namespace Mn
{
	Momodora::Momodora()
	{
	}
	Momodora::~Momodora()
	{
	}
	void Momodora::Initialize()
	{
		_Image = Resources::Load<Image>(L"Momodora",L"..\\Resources\\Momo.bmp");
		GameObject::Initialize();
	}
	void Momodora::Update()
	{
		GameObject::Update();
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();

		if (Input::GetKeyState(eKeyCode::A)==eKeyState::Pressed)
		{
			pos.x -= 100.0f* Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->Pos(pos);
	}

	void Momodora::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		BitBlt(hdc, pos.x, pos.y, _Image->Width(), _Image->Height(), _Image->Hdc(), 0, 0, SRCCOPY);
	}
	void Momodora::Release()
	{
		GameObject::Release();
	}
}