#include "MnSceneManager.h"
#include"MnPlayScene.h"
#include "MnTitleScene.h"

namespace Mn {
	//static �����̱� ������ ������ �޸� �Ҵ��� ���־����
	//�� Ŭ������ �����Ѵٰ� �˷��ִ� ������ ����
	std::vector<Scene*>SceneManager::_Scenes = {};
	Scene* SceneManager::_ActiveScene=nullptr;
	void Mn::SceneManager::Initialize()
	{
		_Scenes.resize((UINT)eScene::Max);
		_Scenes[(UINT)eScene::play] = new PlayScene();
		_Scenes[(UINT)eScene::Title] = new TitleScene();
		_ActiveScene = _Scenes[(UINT)eScene::Title];

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

	void SceneManager::LoadScene(eScene SceneType)
	{
		_ActiveScene->OnExit();
		_ActiveScene = _Scenes[(UINT)SceneType];
		_ActiveScene->OnEnter();
	}

	

}