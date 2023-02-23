#pragma once
#include"MnScene.h"
#include"MnMomodora.h"
#include "MnImage.h"

namespace Mn 
{
	class PlayScene :public Scene
	{
	private:
		Image* _image;
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

