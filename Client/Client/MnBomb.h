#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class Animator;
	class Bomb : public GameObject
	{
	private:
		Animator*	_Animator;
		Collider*	_Collider;
		Image*		_Image;
		Vector2		_Pos;
		float		_Time;
	public:
		Bomb();
		~Bomb();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	private:
		float computeY(int a, int b, int c, float x) { return (a* x* x) + (b * x) + c; }
	};
}
