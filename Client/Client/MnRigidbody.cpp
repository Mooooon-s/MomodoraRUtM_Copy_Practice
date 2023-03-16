#include "MnRigidbody.h"
#include "MnTime.h"
#include "MnTransform.h"
#include "MnGameObject.h"

namespace Mn
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, _Mass(0.0f)
		, _Force(Vector2::Zero)
		, _Accelation(Vector2::Zero)
		, _Velocity(Vector2::Zero)
	{
		_Gravity = Vector2(0.0f, 800.0f);
		_LimitedVelocity = Vector2(200.0f, 1000.0f);
		_Friction = 100.0f;
		_IsGround = true;
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		//F=ma
		//a=F/m
		_Accelation = _Force / _Mass;

		_Velocity += _Accelation * Time::DeltaTime();

		if (_IsGround)
		{
			Vector2 gravity = _Gravity;
			gravity.Normalize();

			float dot = math::Dot(_Velocity, gravity);
			_Velocity -= gravity * dot;
		}
		else
		{
			_Velocity += _Gravity * Time::DeltaTime();
		}

		Vector2 gravity = _Gravity;
		gravity.Normalize();
		float dot = math::Dot(_Velocity, gravity);
		gravity = gravity * dot;

		if (_LimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= _LimitedVelocity.y;
		}

		Vector2 sideVelocity = _Velocity - gravity;
		if (_LimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= _LimitedVelocity.x;
		}

		Transform* tr = Owner()->GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		pos += _Velocity * Time::DeltaTime();
		tr->Pos(pos);
		_Force.Clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
	}
	void Rigidbody::Release()
	{
	}
	void Rigidbody::AddForce(Vector2 force)
	{
		_Force += force;
	}
}