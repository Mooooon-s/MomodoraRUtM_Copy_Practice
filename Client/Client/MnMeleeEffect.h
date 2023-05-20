#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"
#include "MnKaho.h"

namespace Mn
{
	class Animator;
	class Collider;
	class MeleeEffect : public GameObject
	{
	private:
		Kaho*		_kaho;
		Collider*	_Collider;
		Animator*	_Animator;
		eDir		_Dir;
		int			_Attack;
		bool		_IsEnd;
		bool		_IsPlaying;
		bool		_On;
	public:
		MeleeEffect();
		~MeleeEffect();
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
		void Dir(eDir dir) { _Dir = dir; }
		void attack(int attack) { _Attack = attack; }
		void On(bool on) { _On = on; }
	private:
		void melee1Complete();
		void melee2Complete();
		void melee3Complete();
		void airmeleeComplete();
		void effectpos();
		void animation();
		void kahoHumanMeleeCollider();
		void kahoCatMeleeCollider();
	};
}

