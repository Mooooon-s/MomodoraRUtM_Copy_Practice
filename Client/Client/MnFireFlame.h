#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Rigidbody;
	class Collider;
	class FireFlame : public GameObject
	{
	private:
		Rigidbody*	_Rigidbody;
		Collider*	_Collider;
		Image*		_Image;
		Image*		_Map;
		Vector2		_Dir;
		float		_Timer;
		float		_JumpForce;
		int			_Count;
	public:
		FireFlame();
		~FireFlame();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
	public:
		void Dir(Vector2 pos) { _Dir = pos; }
	};
}

