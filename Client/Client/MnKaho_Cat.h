#pragma once
#include "MnGameObject.h"
#include "MnEnum.h"

namespace Mn
{
	class Kaho;
	class Animator;
	class Kaho_Cat : public GameObject
	{
	private:
		enum class ePlayerStatus
		{
			Idle,
			Move,
			Crouch,
			Attack,
		};

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

