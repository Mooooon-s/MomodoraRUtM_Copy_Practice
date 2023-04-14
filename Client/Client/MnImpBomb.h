#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class Kaho;
	class ImpBomb : public GameObject
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
		Rigidbody*	_Rigidbody;
		Kaho*		_kaho;
		eDir		_Dir;
		float		_ThinkTime;
		float		_Hp;
	public:
		ImpBomb();
		~ImpBomb();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release();
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	public:
		void attack();
		void afterAction();
	};
}

