#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class PrayEffect: public GameObject
	{
	private:
		Image* _Image;
	public:
		PrayEffect();
		~PrayEffect();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	};
}

