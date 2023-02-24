#pragma once
#include "MnGameObject.h"
#include "MnImage.h"
	
namespace Mn
{
	class MainMenuBG : public GameObject
	{
	private:
		Image* _Image;
	public:
		MainMenuBG();
		~MainMenuBG();

		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
	};
}

