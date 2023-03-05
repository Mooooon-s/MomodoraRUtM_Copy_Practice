#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Imp :public GameObject
	{
	private:
		enum class eMonStatus
		{
			Move,
			Attack,
			Defence,
		};
		eMonStatus	_Status;
		Animator*	_animator;
		Vector2		_Pos;
		double		_Time;
	public:
		Imp();
		~Imp();

		 void Initialize() override;
		 void Update()override;
		 void Render(HDC hdc)override;
		 void Release()override;
	private:
		void move();
		void attack();
		void defence();
		eMonStatus think();

	};
}

