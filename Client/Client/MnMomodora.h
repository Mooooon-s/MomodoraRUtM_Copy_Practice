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
			Rolling,
			Crouch,
			Jump,
			Melee,
			Range,
			Climb,
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
		int			_Idx;
	public:
		Momodora();
		~Momodora();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	private:
		void move();
		void idle();
		void crouch();
		void rolling();
	};
}
