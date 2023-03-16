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
		float	_Mass;
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
	};
}

