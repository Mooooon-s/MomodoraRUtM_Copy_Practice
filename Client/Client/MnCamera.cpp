#include "MnCamera.h"
#include "Application.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnInput.h"

extern Mn::Application application;

namespace Mn
{
	Vector2 Camera::_Resolution = Vector2::Zero;
	Vector2 Camera::_LookPosition = Vector2::Zero;
	Vector2 Camera::_Distance = Vector2::Zero;
	GameObject* Camera::_Target = nullptr;

	void Camera::Initiailize()
	{
		_Resolution.x = application.Width();
		_Resolution.y = application.Height();
		_LookPosition = (_Resolution / 2.0f);
	}
	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::G))
			_LookPosition.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::J))
			_LookPosition.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::Y))
			_LookPosition.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::H))
			_LookPosition.y += 100.0f * Time::DeltaTime();

		if (_Target != nullptr)
		{
			_LookPosition = _Target->GetComponent<Transform>()->Pos();
		}

		_Distance = _LookPosition - (_Resolution / 2.0f);
	}

	void Camera::CamMove()
	{

	}

	void Camera::Clear()
	{
		_Resolution.x = application.Width();
		_Resolution.y = application.Height();
		_LookPosition = (_Resolution / 2.0f);
		_Distance = Vector2::Zero;
	}

	



}