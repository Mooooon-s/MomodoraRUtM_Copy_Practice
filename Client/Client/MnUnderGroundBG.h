#pragma once
#include "MnGameObject.h"
#include "MnImage.h"
namespace Mn
{
	class UnderGroundBG : public GameObject
	{
	private:
		Image* _Image;
	public:
		UnderGroundBG();
		~UnderGroundBG();
	public:
		void Initialize() override;
		void Render(HDC hdc) override;
	};
}
