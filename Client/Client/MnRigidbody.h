#pragma once
#include "MnComponent.h"

namespace Mn
{
	class Rigidbody : public Component
	{
	private:
		Vector2 _Force;
		Vector2 _Accelation;
		Vector2 _Velocity;
		Vector2 _LimitedVelocity;
		Vector2 _Gravity;
		float	_Mass;
		float	_Friction;
		bool	_IsGround;


	public:
		Rigidbody();
		~Rigidbody();

		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void AddForce(Vector2 force);
	public:
		void SetMass(float mass) { _Mass = mass; }
		void SetGround(bool ground) { _IsGround = ground; }
		bool GetGround() { return _IsGround; }
		Vector2 Velocity() { return _Velocity; }
		void Velocity(Vector2 velocity) { _Velocity = velocity; }
	};
}

