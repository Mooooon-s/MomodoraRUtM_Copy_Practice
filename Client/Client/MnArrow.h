#pragma once
#include "MnGameObject.h"
#include "MnPlayerEnum.h"

namespace Mn
{
	class Animator;
	class Arrow : public GameObject
	{
	private:
		Animator*	_Animator;
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
		void Dir(eDir dir) { _Dir = dir; }
	};
}

