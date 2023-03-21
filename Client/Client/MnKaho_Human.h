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
		bool			_Combo;
		bool			_IsCrouch;
		bool			_IsGround;
		int				_col;
		int				_row;
	public:
		Kaho_Human();
		~Kaho_Human();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void PlayerStatus(ePlayerStatus status) { _PlayerStatus = status; }
		void Dir(eDir dir) { _Dir = dir; }
		eDir Dir() { return _Dir; }
		void Active(eState state) { GameObject::State(state); }
		void animationCtrl();
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
	private:
		void attackComplete();
		void attackCombo1Complete();
		void attackCombo2Complete();
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

