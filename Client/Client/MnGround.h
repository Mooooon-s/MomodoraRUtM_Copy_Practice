#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Ground : public GameObject
	{
	private:
		class Collider* _Collider;
	public:
		Ground();
		~Ground();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	};
}
