#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class FireBall : public GameObject
	{
	private:
		enum class eDir
		{
			R,
			L,
		};
		Collider* _Collider;
		Image*	_FireBall;
		float	_Degree;
		Vector2 _Pos;
		float	_Timer;
		bool	_First;
		class Arsonist* _Boss;
	public:
		FireBall();
		~FireBall();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
	public:
		void PlayerPos(Vector2 pos) { _Pos = pos; }
		void First() { _First = true; }
	};
}

