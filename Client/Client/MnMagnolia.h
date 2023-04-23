#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Rigidbody;
	class Magnolia:public GameObject
	{
	private:
		enum class eMagnoliaState
		{
			Idle,
			pattarn1,
			pattarn2,
			ShowUp,
			DisAppear,
			Land,
		};
		enum class eDir
		{
			R,
			L,
		};
		Image*			_Image;
		Animator*		_Animator;
		Rigidbody*		_Rigidbody;
		eMagnoliaState	_State;
		eDir			_Dir;
		float			_Timer;
		bool			_Jump;
	public:
		Magnolia();
		~Magnolia();
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
		void pattarn1();
		void pattarn2();
		void showUp();
		void disAppear();
		void afterPattarn();
		void afterPattarn2();
		void idle();
	};
}

