#pragma once
#include"MnScene.h"
#include "MnKaho.h"

namespace Mn 
{
	class PlayScene :public Scene
	{
	private:
		Kaho* _kaho;
	public:
		PlayScene();
		~PlayScene();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	public:
		void OnEnter() override;
		void OnExit() override;
	};
}

