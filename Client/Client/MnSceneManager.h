#pragma once
#include"MnScene.h"
#include"MnEnum.h"
#include"MnPlayScene.h"

namespace Mn {
	class SceneManager
	{
	private:
		static std::vector<Scene*> _Scenes;
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
	};
}
