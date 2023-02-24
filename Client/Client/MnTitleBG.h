#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class TitleBG : public GameObject
	{
	private:
		Image* _Image;
	public:
		TitleBG();
		~TitleBG();

		void Initialize() override;
		void Update()override;
		void Render(HDC hdc) override;

	};
}

