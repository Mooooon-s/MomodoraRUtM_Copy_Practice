#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class BossHpBar : public GameObject
	{
	private:
		Image*	_Frame;
		Image*	_Bar;
		float	_Hp;
	public:
		BossHpBar();
		~BossHpBar();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
		void Hp(float hp) { _Hp = hp; }
	};
}

