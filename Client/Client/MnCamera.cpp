#include "MnCamera.h"
#include "Application.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnInput.h"
#include "MnImage.h"

extern Mn::Application application;

namespace Mn
{
	Vector2 Camera::_Resolution = Vector2::Zero;
	Vector2 Camera::_LookPosition = Vector2::Zero;
	Vector2 Camera::_Distance = Vector2::Zero;
	GameObject* Camera::_Target = nullptr;

	Camera::CameraState	Camera::_Type = Camera::CameraState::None;
	Image* Camera::_Cutton=nullptr;
	float Camera::_CuttonAlpha=1.0f;
	float Camera::_AlphaTime=0;
	float Camera::_EndTime=5;

	void Camera::Initiailize()
	{
		_Resolution.x = application.Width();
		_Resolution.y = application.Height();
		_LookPosition = (_Resolution / 2.0f);

		_Type = CameraState::FadeIN;
		_Cutton = Image::Create(L"Cutton", _Resolution.x, _Resolution.y, RGB(0, 0, 0));
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

		if (_AlphaTime < _EndTime)
		{
			//255 - > 1
			_AlphaTime += Time::DeltaTime();
			float ratio = (_AlphaTime / _EndTime);

			if (_Type == CameraState::FadeIN)
			{
				_CuttonAlpha = 1.0f - ratio;
			}
			else if (_Type == CameraState::FadeOUT)
			{
				_CuttonAlpha = ratio;
			}
			else
			{

			}
		}

		_Distance = _LookPosition - (_Resolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		if (_AlphaTime < _EndTime
			&& _Type == CameraState::FadeIN)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (BYTE)(255.0f * _CuttonAlpha);

			AlphaBlend(hdc, 0, 0
				, _Resolution.x, _Resolution.y
				, _Cutton->Hdc()
				, 0, 0
				, _Cutton->Width(), _Cutton->Height()
				, func);
		}
	}

	void Camera::CamReset()
	{
		if (_Type == CameraState::FadeIN)
			_AlphaTime = 0;
		else if (_Type == CameraState::FadeOUT)
			_AlphaTime = 1;
	}

	void Camera::CamReset(float alphatime)
	{
		if (_Type == CameraState::FadeIN)
			_AlphaTime = 0;
		else if (_Type == CameraState::FadeOUT)
			_AlphaTime = 1;
		_EndTime = alphatime;
	}

	void Camera::Clear()
	{
		_Resolution.x = application.Width();
		_Resolution.y = application.Height();
		_LookPosition = (_Resolution / 2.0f);
		_Distance = Vector2::Zero;
	}

}