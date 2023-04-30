#pragma once
#include"MnScene.h"
#include"MnEnum.h"
#include "MnSound.h"
#include "MnResources.h"

namespace Mn {
	class SceneManager
	{
	private:
		static Scene* _ActiveScene;
		static std::vector<Scene*> _Scenes;

		static bool _Iscat;
		static float _Hp;
		static int _Item;
		static bool _WallDown;
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
		static void SetDontDestroy(float hp, bool iscat, int idx);
		static float GetDontDestroyHP();
		static bool GetDontDestroyCat();
		static int GetDontDestroyIdx();
		static bool GetWall() { return _WallDown; }
		static void SetWall(bool wall) { _WallDown = wall; }
		static void StopSound(std::wstring name) { Resources::Find<Sound>(name)->Stop(true); }
	};
}
