#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"

namespace Mn
{
	class Kaho;
	class Animator;
	class Rigidbody;
	class Kaho_Cat : public GameObject
	{
	private:
		ePlayerStatus	_PlayerStatus;
		Rigidbody*		_Rigidbody;
		Animator*		_Animator;
		Vector2			_Pos;
		eState			_State;
		eDir			_Dir;
		float			_Dashtime;
		float			_HurtTime;
		float			_DamageTime;
		float			_AlphaTime;
		float			_Jumpforce;
		float			_MoveSpeed;
		float			_CoolTime;
		float			_Hp;
		bool			_Death;
		bool			_Switch;
		bool			_DashOn;
		bool			_GetDamage;
		bool			_Combo;
		int				_AlphaDegree;
		int				_DoubleJump;
		int				_ComboCount;
	public:
		Kaho_Cat();
		~Kaho_Cat();
	public:
		 void Initialize()override;
		 void Update()override;
		 void Render(HDC hdc)override;
		 void Release() override;
		 
		 void OnCollisionEnter(class Collider* other) override;
		 void OnCollisionStay(class Collider* other) override;
	public:
		void PlayerStatus(ePlayerStatus status) { _PlayerStatus = status; }
		void Dir(eDir dir) { _Dir = dir; }
		eDir Dir() { return _Dir; }
		void Active(eState state) { GameObject::State(state); }
		float MoveSpeed() { return _MoveSpeed; }
		void SyncHp(float hp) { _Hp = hp; }
		float SyncHp() { return _Hp; }
		bool Switch() { return _Switch; }
		void Switch(bool swich) { _Switch = swich; }
		void animationCtrl();
	private:
		void idle();
		void move();
		void attack();
		void crouch();
		void roll();
		void jump();
		void fall();
		void hurt();
		void useItem();
		void alpha();
	private:
		void attackStart();
		void attackCombo1Start();
		void attackCombo2Start();
		void attackAirStart();
	private:
		void attackComplete();
		void attackCombo1Complete();
		void attackCombo2Complete();
		void rollComplete();
		void preDashComplete();
		void dashComplete();
		void postDashComplete();

		void preCrouchComplete();
		void postCrouchComplete();

		void RunComplete();

		void landingComplete();
		void afterUseItem();

	};
}

