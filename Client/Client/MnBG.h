#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn {
	class BG : public GameObject
	{
	private:
		Image* _image;
	public:
		BG();
		~BG();

		void Initialize();
		void Update();
		void Render(HDC hdc);


	};
}
