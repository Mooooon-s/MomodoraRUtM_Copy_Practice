#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Animator;
	class Rigidbody;
	class Collider;
	class Image;
	class Kaho;
	class Sound;
	class ImpKnife : public GameObject
	{
	private:
		enum class eMonStatus
		{
			Move,
			Fall,
			Attack,
			Idle,
			Hurt,
			Death,
		};
		enum class eDir 
		{
			R,
			L,
		};
		enum class eSound
		{
			idle1,
			idle2,
			hurt,
			death,
		};
		std::vector<Sound*> _Soundpack;
		Rigidbody*	_Rigidbody;
		Collider*	_Collider;
		Animator*	_Animator;
		Kaho*		_kaho;
		Image*		_Image;
		eMonStatus  _MonState;
		eDir		_Dir;
		Vector2		_Pos;
		double		_ThinkTime;
		double		_SoundTime;
		double		_HurtTime;
		float		_Hp;
		int			_ActionCount;
	public:
		ImpKnife();
		~ImpKnife();
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
		void think();
		void move();
		void attack();
		void hurt();
		void fall();
		void idle();
		void death();
		void animatorCntrl();
		void trowKnife();
	};

}