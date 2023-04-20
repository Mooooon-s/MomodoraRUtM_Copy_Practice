#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class PlayerHpBar : public GameObject
	{
	private:
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

