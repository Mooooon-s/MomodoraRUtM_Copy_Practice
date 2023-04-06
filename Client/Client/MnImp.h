#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Rigidbody;
	class Collider;
	class Imp :public GameObject
	{
	private:
		enum class eMonStatus
		{
			Move,
			Attack,
			Defence,
			Hurt,
		};
		enum class eDir
		{
			R,
			L,
		};
		class Kaho* _kaho;
		eMonStatus	_Status;
		Rigidbody*	_Rigidbody;
		Collider*	_Collider;
		Animator*	_Animator;
		Vector2		_Pos;
		eDir		_Dir;
		double		_HurtTime;
		double		_ThinkTime;
		int			_Hp;
	public:
		Imp();
		~Imp();

		 void Initialize() override;
		 void Update()override;
		 void Render(HDC hdc)override;
		 void Release()override;
	public:
		void OnCollisionEnter(class Collider* other);
		void OnCollisionStay(class Collider* other);
		void OnCollisionExit(class Collider* other);
	private:
		void move();
		void attack();
		void defence();
		void hurt();
		void animationCntrl();
		eMonStatus think();

	};
}

