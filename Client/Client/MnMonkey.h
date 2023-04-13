#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class Monkey : public GameObject
	{
	private:
		enum class eMonStatus
		{
			Idle,
			Move,
			Attack,
			Hurt,
			Death
		};
		enum class eDir
		{
			R,
			L,
		};
		eMonStatus	_MonStatus;
		Animator*	_Animator;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
		Image*		_Image;
		eDir		_Dir;
		double		_HurtTime;
		float		_MoveSpeed;
		float		_HP;
		class Kaho* _Kaho;
	public:
		Monkey();
		~Monkey();
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
		void animationCtrl();
		void hurt();
		void idle();
		void attack();
		void death();
		void move();
	private:
		void afterHurt();
		void afterDeath();
		void afterAttack();

	};
}

