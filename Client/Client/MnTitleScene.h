#pragma once
#include "MnScene.h"

namespace Mn
{
	class TitleScene: public Scene
	{
	private:

	public:
		TitleScene();
		~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc)override;
	public:
		void OnEnter() override;
		void OnExit()  override;
	};
}

