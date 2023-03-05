#pragma once
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn {
	class Animator;
	class Momodora : public GameObject
	{
	private:
		enum class eStatus
		{
			Idle,
			Move,
			Death,
			Rolling,
			Crouch,
			Jump,
			Melee,
			Range,
			Climb,
			UseItem,
			GetItem,
			Hurt,
			Max,
		};
		
		enum class eDir
		{
			Left,
			Right
		};
	private:
		Animator*	_animator;
		eStatus		_Status;
		eDir		_Dir;
		float		_Time;
		bool		_IsJumped;
		bool		_IsCrouch;
		bool		_bDoubleJump;
		int			_Idx;
		int			_col;
		int			_row;


	public:
		Momodora();
		~Momodora();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	private:
		void playAnimationDirection(void);
	private:
		void move();
		void idle();
		void jump();
		void hurt();
		void climb();
		void death();
		void crouch();
		void rolling();
		void getItem();
		void useItem();
		void meleeAttack();
		void rangeAttack();

	};
}
