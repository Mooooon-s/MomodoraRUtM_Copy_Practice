#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class Wall : public GameObject
	{
	private:
		Image*		_Image;
		Collider*	_Collider;
		float		_Timer;
		int			_Num;
	public:
		Wall();
		~Wall();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
	};
}

