#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class TitleUI : public GameObject
	{
	private:
		Image* _image;
	public:
		TitleUI();
		~TitleUI();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc)override;
		void Release()override;
	};
}

