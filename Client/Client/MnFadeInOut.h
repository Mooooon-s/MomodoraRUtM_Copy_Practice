#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class FadeInOut : public GameObject
	{
	private:
		BLENDFUNCTION	func;
		Image*			_Image;
		bool			_IsFade;
		int				_alpha;
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void FadeIN();
		void FadeOUT();

		void IsFade(bool b) { _IsFade = b; }
	};
}

