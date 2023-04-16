#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Collider;
	class MonMeleeAttack : public GameObject
	{
	private:
		Collider*	_Collider;
		float		_Time;
	public:
		MonMeleeAttack();
		~MonMeleeAttack();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	public:
		void Done();
	};
}

