#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Kaho_Cat : public GameObject
	{
	private:
		enum class ePlayerStatus
		{
			Idle,
			Move,
			Attack,
		};
		enum class eDir
		{
			R,
			L,
		};
		ePlayerStatus	_PlayerStatus;
		Animator*		_Animator;
		Vector2			_Pos;
		eDir			_Dir;
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
		void animationCtrl();

	};
}

