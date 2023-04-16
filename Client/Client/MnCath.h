#pragma once
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnImage.h"

namespace Mn
{ 
	class Rigidbody;
	class Collider;
	class Cath : public GameObject
	{
	private:
		Image*		_Image;
		Animator*	_Animator;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
	public:
		Cath();
		~Cath();
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

