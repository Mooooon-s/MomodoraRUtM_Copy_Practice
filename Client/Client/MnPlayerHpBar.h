#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Kaho;
	class PlayerHpBar : public GameObject
	{
	private:
		Kaho*		_Kaho;
		Image*		_HpBarFrame;
		Image*		_HpBar;
		float		_Hp;

	public:
		PlayerHpBar();
		~PlayerHpBar();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void Hp(float hp) { _Hp = hp; }
		float Hp() { return _Hp; }
	};
}

