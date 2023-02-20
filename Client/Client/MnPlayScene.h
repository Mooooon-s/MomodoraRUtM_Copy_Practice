#pragma once
#include"MnScene.h"
#include"MnMomodora.h"

namespace Mn 
{
	class PlayScene :public Scene
	{
	public:
		PlayScene();
		~PlayScene();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};
}

