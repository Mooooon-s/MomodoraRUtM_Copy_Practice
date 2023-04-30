#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Sound;
	class Animator;
	class Collider;
	class Staff : public GameObject
	{
	private:
		Animator*	_Animator;
		Collider*	_Collider;
		Image*		_Image;
		Vector2		_DirVec;
		Sound*		_StaffRotatSound;
		float		_GetBack;
		float		_Timer;
		bool		_Return;
		int			_Count;
	public:
		Staff();
		~Staff();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
	public:
		void DirVector(Vector2 dir) { _DirVec = dir; }
		bool Done() { return _Return; }
	};
}

