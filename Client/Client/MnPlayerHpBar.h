#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class PlayerHpBar : public GameObject
	{
	private:
		Animator*	_Animator;
		Image*		_HpBarFrame;
		Image*		_HpBar;
	public:
		PlayerHpBar();
		~PlayerHpBar();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	};
}

