#include "MnSceneManager.h"
#include "MnTitleScene.h"

namespace Mn {
	//static �����̱� ������ ������ �޸� �Ҵ��� ���־����
	//�� Ŭ������ �����Ѵٰ� �˷��ִ� ������ ����
	std::vector<Scene*>SceneManager::_Scenes = {};
	void Mn::SceneManager::Initialize()
	{
		_Scenes.resize((UINT)eScene::Max);
		_Scenes[(UINT)eScene::play] = new PlayScene();
		//_Scenes[(UINT)eScene::Title] = new TitleScene();

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
		/*for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;
			scene->Render(hdc);
		}*/

		_Scenes[(UINT)eScene::play]->Render(hdc);

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