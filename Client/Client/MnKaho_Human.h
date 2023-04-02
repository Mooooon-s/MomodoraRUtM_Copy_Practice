#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"
#include "MnImage.h"

namespace Mn
{
	class Animator;
	class Rigidbody;
	class Kaho_Human : public GameObject
	{
	private:
		ePlayerStatus	_PlayerStatus;
		Animator*		_Animator;
		Rigidbody*		_Rigidbody;
		Vector2			_pos;
		Image*			_Image;
		eDir			_Dir;
		float			_DashCharge;
		float			_HurtTime;
		float			_AlphaTime;
		float			_DamageTime;
		float			_Jumpforce;
		bool			_Combo;
		bool			_IsCrouch;
		bool			_IsGround;
		bool			_GetDamage;
		int			_DoubleJump;
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
		void PlayerStatus(ePlayerStatus status) { _PlayerStatus = status; }
		void Dir(eDir dir) { _Dir = dir; }
		eDir Dir() { return _Dir; }
		void Active(eState state) { GameObject::State(state); }
		void animationCtrl();
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
	};
}

