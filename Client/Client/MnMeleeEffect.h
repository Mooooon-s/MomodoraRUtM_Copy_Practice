#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Collider;
	class MeleeEffect : public GameObject
	{
	private:
		Animator* _Animator;
	public:
		MeleeEffect();
		~MeleeEffect();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	};
}

