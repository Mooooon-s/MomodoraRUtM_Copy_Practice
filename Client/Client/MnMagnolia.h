#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Magnolia:public GameObject
	{
	private:
		Image* _Image;
		Animator* _Animator;
	public:
		Magnolia();
		~Magnolia();
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

