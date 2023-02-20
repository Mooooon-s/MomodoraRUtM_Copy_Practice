#include "MnMomodora.h"
#include "MnInput.h"



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
		// stock 오브젝트
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		//Rectangle(mHdc, -1, -1, 1601, 901);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, _Pos.x, _Pos.y, _Pos.x + 100, _Pos.y + 100);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
	void Momodora::Release()
	{
		GameObject::Release();
	}
}