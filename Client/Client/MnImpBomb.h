#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Sound;
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
		Sound*		_Sound1;
		Sound*		_Sound2;
		Animator*	_Animator;
		Collider*	_Collider;
		Rigidbody*	_Rigidbody;
		Kaho*		_kaho;
		eDir		_Dir;
		float		_ThinkTime;
		float		_SoundTime;
		float		_HurtTime;
		float		_Hp;
		bool		_Ishurt;
		bool		_Death;
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

