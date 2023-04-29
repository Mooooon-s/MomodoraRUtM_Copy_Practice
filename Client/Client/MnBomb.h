#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Sound;
	class Collider;
	class Animator;
	class Rigidbody;
	class Bomb : public GameObject
	{
	private:
		Animator*	_Animator;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
		Image*		_Image;
		Image*		_GroundImage;
		Sound*		_Explosion;
		Vector2		_Pos;
		float		_Time;
		int			_Dir;
		bool		_blowUp;
	public:
		Bomb();
		~Bomb();
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
		void Dir(int dir) { _Dir = dir; }
		bool BlowUp() { return _blowUp; }
	private:
		float computeY(int a, int b, int c, float x) { return (a* x* x) + (b * x) + c; }
		void afterBlowUp();
		void blowUp();
	};
}
