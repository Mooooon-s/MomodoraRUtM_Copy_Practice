#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"

namespace Mn
{
	class Kaho;
	class Animator;
	class Kaho_Cat : public GameObject
	{
	private:
		ePlayerStatus	_PlayerStatus;
		Vector2			_Pos;
		Animator*		_Animator;
		eDir			_Dir;
		float			_Dashtime;
		bool			_Combo;
		bool			_IsGround;
		bool			_IsActive;
	public:
		Kaho_Cat();
		~Kaho_Cat();
	public:
		 void Initialize()override;
		 void Update()override;
		 void Render(HDC hdc)override;
		 void Release() override;
	public:
		void PlayerStatus(ePlayerStatus status) { _PlayerStatus = status; }
		void Dir(eDir dir) { _Dir = dir; }
		eDir Dir() { return _Dir; }
		void Active(bool active) { _IsActive = active; }
		void animationCtrl();
	private:
		void idle();
		void move();
		void attack();
		void crouch();
		void roll();
		void jump();
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


	};
}

