#include "MnSceneManager.h"

namespace Mn {
	//static 변수이기 때문에 전역에 메모리 할당을 해주어야함
	//이 클래스에 존재한다고 알려주는 느낌도 있음
	std::vector<Scene*>SceneManager::_Scenes = {};
	void Mn::SceneManager::Initialize()
	{
		_Scenes.resize((UINT)eScene::Max);
		_Scenes[(UINT)eScene::play] = new PlayScene();

		for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}
	}

	void Mn::SceneManager::Update()
	{
		for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;
			scene->Update();
		}
	}

	void Mn::SceneManager::Render(HDC hdc)
	{
		for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;
			scene->Render(hdc);
		}
	}

	void Mn::SceneManager::Release()
	{
		for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}
}