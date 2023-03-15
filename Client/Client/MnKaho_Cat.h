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
		bool			_Combo;
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
	private:
		void idle();
		void move();
		void attack();
		void crouch();
	private:
		void attackComplete();
		void attackCombo1Complete();
		void attackCombo2Complete();
		void animationCtrl();

	};
}

