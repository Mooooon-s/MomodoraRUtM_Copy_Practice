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
		void SetMass(float mass) { _Mass = mass; }
		void AddForce(Vector2 force);
		void SetGround(bool ground) { _IsGround = ground; }
	};
}

