#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Rigidbody;
	class Collider;
	class MonMeleeAttack;
	class LupiarBall;
	class Kaho;
	class Lupiar :public GameObject
	{
	private:
		enum class eDir
		{
			R,
			L,
		};
		enum class eLupiarState
		{
			Idle,
			Hurt,
			Death,
			Roll,
			Pattarn1,
			Pattarn2,
			Pattarn3,
			Pattarn4,
		};
		Image*			_Image;
		Animator*		_Animator;
		Rigidbody*		_Rigidbody;
		Collider*		_Collider;
		LupiarBall*		_LupiarBall;
		MonMeleeAttack* _MeleeAttack;
		Kaho*			_Kaho;
		eLupiarState	_State;
		eDir			_Dir;
		float			_Ready;
		float			_HurtTime;
		float			_KnockBack;
		int				_Count;
		float			_MoveSpeed;
		bool			_Dash;
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
	private:
		void think();
		void idle();
		void hurt();
		void death();
		void roll();
		void pattarn1();
		void pattarn2();
		void pattarn3();
		void pattarn4();
		void animationCtrl();
	private:
		void afterAction();
		void pattarn1Dash();
		void pattarn1Attack();
		void pattarn2Attack();
		void pattarn3Attack();
		void pattarn4Attack();
	};
}

