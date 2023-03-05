#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn {
	class BG : public GameObject
	{
	private:
		Image*		_image;

		HBITMAP		_PreBitmap;
		HDC			_PreHDC;
	public:
		BG();
		~BG();

		void Initialize();
		void Update();
		void Render(HDC hdc);


	};
}
