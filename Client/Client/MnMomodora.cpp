#include "MnMomodora.h"
#include "MnInput.h"
#include "MnResources.h"



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
		if (Input::GetKeyState(eKeyCode::A)==eKeyState::Pressed)
		{
			_Pos.x -= 100.0f* Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			_Pos.x += 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			_Pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			_Pos.y += 100.0f * Time::DeltaTime();
		}
	}

	void Momodora::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		BitBlt(hdc, _Pos.x, _Pos.y, _Image->Width(), _Image->Height(), _Image->Hdc(), 0, 0, SRCCOPY);
	}
	void Momodora::Release()
	{
		GameObject::Release();
	}
}