#pragma once
#include"MnScene.h"
#include"MnEnum.h"


namespace Mn {
	class SceneManager
	{
	private:
		static Scene* _ActiveScene;
		static std::vector<Scene*> _Scenes;
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Destroy();
		static void Release();
	public:
		static void LoadScene(eSceneType SceneType);
		static Scene* ActiveScene() { return _ActiveScene; }
		static void ActiveScene(Scene* scene) { _ActiveScene = scene; }
	};
}
