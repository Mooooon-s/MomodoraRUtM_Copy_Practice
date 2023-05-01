#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class Title_Letter : public GameObject
	{
	private:
		Image* _Image;
		Image* _CatImage;
		Image* _StartFont;
	public:
		Title_Letter();
		~Title_Letter();
	public:
		void Initialize()		override;
		void Update()			override;
		void Render(HDC hdc)	override;
		void Release()			override;
	};
}

