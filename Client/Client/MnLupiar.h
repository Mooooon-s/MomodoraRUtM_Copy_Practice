#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Rigidbody;
	class Collider;
	class Lupiar :public GameObject
	{
	private:
		Image*		_Image;
		Animator*	_Animator;
		Rigidbody*	_Rigidbody;
		Collider*	_Collider;
	public:
		Lupiar();
		~Lupiar();
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

