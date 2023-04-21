#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class Flame : public GameObject
	{
	private:
		Collider* _Collider;
		Image* _Flame;
		float  _Timer;
	public:
		Flame();
		~Flame();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	};
}

