#pragma once
#include "MnGameObject.h"
#include "MnImage.h"
#include "MnFireBall.h"
#include "MnFireFlame.h"
#include "MnBossHpBar.h"

namespace Mn
{
	class Animator;
	class Rigidbody;
	class Collider;
	class Arsonist : public GameObject
	{
	private:
		enum class eMonStatus
		{
			Idle,
			Move,
			Attack,
			Hurt,
			Pattarn1,
			Pattarn2,
			Pattarn3,
			BackStep,
			Death,
		};
		enum class eDir
		{
			R,
			L,
		};
		eMonStatus	_MonStatus;
		Animator*	_Animator;
		Rigidbody*	_Rigidbody;
		Collider*	_Collider;
		Image*		_Image;
		FireBall*	_FireBall;
		FireFlame*	_FireFlame;
		BossHpBar*	_HpBar;
		eDir		_Dir;
		Vector2		_TeleportPos;
		double		_time;
		bool		_afterAction;
		bool		_Teleporting;
		int			_Count;
		float		_HurtTime;
		float		_KnockBack;
		float		_Ready;
		float		_Hp;
		class Kaho* _Kaho;
	public:
		Arsonist();
		~Arsonist();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc)override;
		void Release()override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	public:
		void Teleport(bool teleport) { _Teleporting = teleport; }
		bool Teleport() { return _Teleporting; }
	private:
		void animationCtrl();
		void think();
		void idle();
		void move();
		void hurt();
		void death();
		void attack();
		void pattarn1();
		void pattarn2();
		void pattarn3();
		void backStep();
		void beforeAttack();
		void afterAttack();
		void fire();
		void waitTeleport();
		void makeFlame();
		void makeFireBall();
	};
}

