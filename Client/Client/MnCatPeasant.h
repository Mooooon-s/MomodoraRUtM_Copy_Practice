#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class CatPeasant : public GameObject
	{
	private:
		enum class eMonstate
		{
			Idle,
			Attack,
			Catch,
			Hurt,
			Death,
		};
		enum class eDir
		{
			R,
			L,
		};
		Image*		_Image;
		Animator*	_Animator;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
		eMonstate	_MonState;
		eDir		_Dir;
		bool		_HaveStaff;
		float		_Ready;
		class Kaho* _Kaho;
		class Staff* _Staff;
	public:
		CatPeasant();
		~CatPeasant();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	private:
		void animationCtrl();
		void idle();
		void staff();
		void throwStaff();
	};
}

