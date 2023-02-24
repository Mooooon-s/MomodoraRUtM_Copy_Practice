#pragma once
#include "MnScene.h"

namespace Mn
{
	class MainMenuScene : public Scene
	{
	public:
		MainMenuScene();
		~MainMenuScene();

		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	};
}
