#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class Animator;
	class Arsonist : public GameObject
	{
	private:
		enum class eMonStatus
		{
			Idle,
			Move,
			Attack,
			Hurt,
			Skill,
		};
		enum class eDir
		{
			R,
			L,
		};
		eMonStatus	_MonStatus;
		Animator*	_Animator;
		Image*		_Image;
		eDir		_Dir;
		double		_time;
	public:
		Arsonist();
		~Arsonist();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc)override;
		void Release()override;
	private:
		void animationCtrl();
		void think();
		

	};
}

