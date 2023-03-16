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
		, _IsGround(false)
	{
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