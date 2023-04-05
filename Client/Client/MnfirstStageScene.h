#pragma once
#include "MnScene.h"
#include "MnKaho.h"

namespace Mn
{
	class firstStageScene : public Scene
	{
	private:
		static Kaho* _kaho;
		Kaho_Human* _KahoHuman;
		Kaho_Cat* _KahoCat;
	public:
		firstStageScene();
		~firstStageScene();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnEnter() override;
		void OnExit() override;
	public:
		static Kaho* GetKaho() { return _kaho; }
	};
}

