#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"

namespace Mn
{
	class Animator;
	class Collider;
	class Arrow : public GameObject
	{
	private:
		Animator*	_Animator;
		Collider*	_Collider;
		bool		_Hit;
		bool		_IsEnd;
		eDir		_Dir;
	public:
		Arrow();
		~Arrow();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
	public:
		void Dir(eDir dir) { _Dir = dir; }
		void Hit();
	private:
		void destroy();
	};
}

