#include "MnSceneManager.h"
#include"MnPlayScene.h"
#include "MnTitleScene.h"
#include "MnMainMenuScene.h"
#include "MnCollisionManager.h"

namespace Mn {
	//static �����̱� ������ ������ �޸� �Ҵ��� ���־����
	//�� Ŭ������ �����Ѵٰ� �˷��ִ� ������ ����
	std::vector<Scene*>SceneManager::_Scenes = {};
	Scene* SceneManager::_ActiveScene=nullptr;

	void Mn::SceneManager::Initialize()
	{
		_Scenes.resize((UINT)eSceneType::Max);

		_Scenes[(UINT)eSceneType::Title] = new TitleScene();
		_Scenes[(UINT)eSceneType::MainMenu] = new MainMenuScene();
		_Scenes[(UINT)eSceneType::play] = new PlayScene();

		_ActiveScene = _Scenes[(UINT)eSceneType::Title];

		for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}
	}

	void Mn::SceneManager::Update()
	{
		_ActiveScene->Update();
	}

	void Mn::SceneManager::Render(HDC hdc)
	{
		_ActiveScene->Render(hdc);
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

	void SceneManager::LoadScene(eSceneType SceneType)
	{
		_ActiveScene->OnExit();
		CollisionManager::Clear();
		_ActiveScene = _Scenes[(UINT)SceneType];
		_ActiveScene->OnEnter();
	}

	

}