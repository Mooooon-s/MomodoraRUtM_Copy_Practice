#pragma once
#include "MnGameObject.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnArsonist.h"
#include "MnNpcMelee.h"

namespace Mn
{ 
	class Rigidbody;
	class Collider;
	class Cath : public GameObject
	{
	private:
		enum class eNpcState
		{
			Idle,
			Attack,
			Move,
			Hurt,
		};
		enum class eDir
		{
			R,
			L,
		};
		Image*		_Image;
		Animator*	_Animator;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
		Arsonist*	_Boss;
		NpcMelee*	_Melee;
		eNpcState	_NpcState;
		eDir		_Dir;
		float		_Ready;
		float		_Hurt;
		bool		_AfterAction;
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
	private:
		void think();
		void idle();
		void move();
		void attack();
		void hurt();
		void afterAction();
		void animationCtrl();
		void meleeAttack();
		void meleeAttackDone();
	};
}

