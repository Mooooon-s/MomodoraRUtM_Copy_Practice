#pragma once
#include "MnGameObject.h"
class Image;
namespace Mn
{
	class Stage3BG : public GameObject
	{
	private:
		Image* _Image;
	public:
		Stage3BG();
		~Stage3BG();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
	};
}

