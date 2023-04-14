#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Collider;
	class Knife : public GameObject
	{
	private:
		enum class eDir
		{
			R,
			L,
		};
		Image*		_Image;
		Animator*	_Animator;
		Collider*	_Collider;
		bool		_Hit;
		eDir		_Dir;
	public:
		Knife();
		~Knife();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	public:
		void Hit();
		void DirR();
		void DirL();
	};
}

