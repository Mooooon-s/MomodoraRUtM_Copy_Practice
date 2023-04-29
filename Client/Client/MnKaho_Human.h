#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"
#include "MnImage.h"
#include "MnPrayEffect.h"

#include "MnSound.h"

namespace Mn
{
	class Animator;
	class Rigidbody;
	class Kaho_Human : public GameObject
	{
	private:
		enum class eSound
		{
			Walk,
			Hurt,
			Pray,
			UseItem,
			Shoot,
			Death,
			Jump,
			Roll,
			AirRoll,
			Attack1,
			Attack2,
			Attack3,
		};
		std::vector<Sound*> _SoundPack;
		ePlayerStatus	_PlayerStatus;
		Animator*		_Animator;
		Rigidbody*		_Rigidbody;
		PrayEffect*		_PrayEffect;
		Vector2			_pos;
		Vector2			_RevivalPos;
		Image*			_Image;
		eDir			_Dir;
		float			_DashCharge;
		float			_HurtTime;
		float			_AlphaTime;
		float			_DamageTime;
		float			_Jumpforce;
		float			_MoveSpeed;
		float			_CoolTime;
		float			_Hp;
		bool			_DashOn;
		bool			_Combo;
		bool			_IsCrouch;
		bool			_IsGround;
		bool			_GetDamage;
		bool			_Death;
		bool			_Switch;
		int				_ComboCount;
		int				_DoubleJump;
		int				_col;
		int				_row;
		int				_AlphaDegree;
	public:
		Kaho_Human();
		~Kaho_Human();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;

		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	public:
		float MoveSpeed() { return _MoveSpeed; }
		void PlayerStatus(ePlayerStatus status) { _PlayerStatus = status; }
		void Dir(eDir dir) { _Dir = dir; }
		eDir Dir() { return _Dir; }
		void Active(eState state) { GameObject::State(state); }
		void SyncHp(float hp) { _Hp = hp; }
		float SyncHp() { return _Hp; }
		void animationCtrl();
		bool Switch() { return _Switch; }
		void Switch(bool swich ) { _Switch = swich; }
	private:
		void alpha();
	private:
		void idle();
		void move();
		void attack();
		void shoot();
		void crouch();
		void jump();
		void fall();
		void roll();
		void useItem();
		void hurt();
	private:
		void attackStart();
		void attackComplete();
		void attackCombo1Start();
		void attackCombo1Complete();
		void attackCombo2Start();
		void attackCombo2Complete();
		void airAttackStart();
		void airAttackComplete();
		void crouchRangeStart();
		void crouchRangeComplete();
		void airRangeStart();
		void airRangeComplete();
		void beforeRange();
		void afterRange();
		void afterRoll();
		void afterUseItem();
		void riseUp();
		void endRun();
		void landingComplete();
		void preDashComplete();
		void DashComplete();
		void postDashComplete();
		void pray();
		void afterpray();
		void afterDeath();
		void walkSound();
	};
}

