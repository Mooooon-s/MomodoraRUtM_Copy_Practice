#pragma once
#include "MnGameObject.h"
#include "MnMonMeleeAttack.h"
namespace Mn
{
	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class Kaho;
	class MagnoliaBoss : public GameObject
	{
	private:
		enum class eMagnolia
		{
			Idle,
			Hurt,
			Attack,
			ShowUp,
			Disappear,
			Death,
		};
		enum class eDir
		{
			R,
			L,
		};
		Image*			_Image;
		Animator*		_Animator;
		Collider*		_Collider;
		Rigidbody*		_Rigidbody;
		MonMeleeAttack* _Melee;
		eMagnolia		_State;
		Kaho*			_Kaho;
		eDir			_Dir;
		float			_Timer;
		bool			_Move;
		bool			_On;
	public:
		MagnoliaBoss();
		~MagnoliaBoss();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
	private:
		void idle();
		void showUp();
		void attack();
		void disappear();
		void attackMove();
		void attackCollider();
		void animationCtrl();
	};
}

