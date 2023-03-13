#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class Animator;
	class Kaho_Human : public GameObject
	{
	private:
		enum class ePlayerStatus

		{
			Idle,
			Move,
			Attack,
			Crouch,
			Jump,
			Shoot,
			Roll,
			UseItem,
		};
		enum class eDir
		{
			R,
			L,
		};
		ePlayerStatus	_PlayerStatus;
		Animator*		_Animator;
		Vector2			_pos;
		Image*			_Image;
		eDir			_Dir;
		bool			_Combo;
		bool			_IsCrouch;
		bool			_IsJump;
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
	private:
		void idle();
		void move();
		void attack();
		void animationCtrl();
		void shoot();
		void crouch();
		void jump();
		void roll();
		void useItem();
	private:
		void attackComplete();
		void attackCombo1Complete();
		void attackCombo2Complete();

		void airAttackComplete();

		void CrouchRangeStart();
		void CrouchRangeComplete();

		void beforeRange();
		void afterRange();

		void afterRoll();
		void afterUseItem();

		void riseUp();

		void EndRun();

	};
}

