#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Image;
	class Rigidbody;
	class Collider;
	class BigPlant : public GameObject
	{
	private:
		enum class eMonStats
		{
			Idle,
			Attack,
			Move,
		};
		enum class eDir
		{
			R,
			L,
		};
		Rigidbody*	_Rigidbody;
		Animator*	_Animator;
		Collider*	_Collider;
		Image*		_Image;
		eDir		_Dir;
		eMonStats   _MonState;
		class Kaho* _Kaho;
	public:
		BigPlant();
		~BigPlant();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	private:
		void idle();
		void move();
		void attack();
		void animatorCntrl();
		void beforAttack();
		void afterAttack();
	};
}

