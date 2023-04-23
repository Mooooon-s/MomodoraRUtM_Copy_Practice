#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class Rigidbody;
	class LupiarBall : public GameObject
	{
	private:
		Image*		_Image;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
		Vector2		_DirVec;
		float*		_Timer;
		std::vector<Vector2> Fpos;
	public:
		LupiarBall();
		~LupiarBall();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void StartPos(Vector2 pos);
		void DirVector(Vector2 dir) { _DirVec = dir; }
	};
}

