#pragma once
#include "MnScene.h"
#include "MnFadeInOut.h"
namespace Mn
{
	class TitleScene: public Scene
	{
	private:
		FadeInOut* fadeInOut;
	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;
		virtual void Release() override;
	public:
		void OnEnter() override;
		void OnExit()  override;
	};
}

