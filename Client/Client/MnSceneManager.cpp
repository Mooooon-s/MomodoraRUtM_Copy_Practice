#include "MnSceneManager.h"
#include"MnPlayScene.h"
#include "MnTitleScene.h"
#include "MnMainMenuScene.h"
#include "MnCollisionManager.h"
#include "MnCamera.h"
#include "MnToolScene.h"
#include "MnfirstStageScene.h"
#include "MnStage_1_2.h"
#include "MnStage_1_3.h"
#include "MnStage1_Boss.h"

#include "MnStage2_1.h"
#include "MnStage2_2.h"
#include "MnStage2_3.h"

#include "MnStage3_1.h"
#include "MnStage3_2.h"
#include "MnStage3_3.h"
#include "MnStage_Ending.h"

namespace Mn {
	//static 변수이기 때문에 전역에 메모리 할당을 해주어야함
	//이 클래스에 존재한다고 알려주는 느낌도 있음
	std::vector<Scene*>SceneManager::_Scenes = {};
	Scene* SceneManager::_ActiveScene=nullptr;
	float SceneManager::_Hp = 100;
	bool SceneManager::_Iscat = false;
	int SceneManager::_Item = 0;
	bool SceneManager::_WallDown = false;

	void Mn::SceneManager::Initialize()
	{
		_Scenes.resize((UINT)eSceneType::Max);

		_Scenes[(UINT)eSceneType::Title] = new TitleScene();
		_Scenes[(UINT)eSceneType::MainMenu] = new MainMenuScene();
		_Scenes[(UINT)eSceneType::play] = new PlayScene();
		_Scenes[(UINT)eSceneType::Stage1] = new firstStageScene();
		_Scenes[(UINT)eSceneType::stage1_2] = new Stage_1_2();
		_Scenes[(UINT)eSceneType::stage1_3] = new Stage_1_3();
		_Scenes[(UINT)eSceneType::stage1_Boss] = new Stage1_Boss();
		_Scenes[(UINT)eSceneType::stage2_1] = new Stage2_1();
		_Scenes[(UINT)eSceneType::stage2_2] = new Stage2_2();
		_Scenes[(UINT)eSceneType::stage2_3] = new Stage2_3();
		_Scenes[(UINT)eSceneType::stage3_1] = new Stage3_1();
		_Scenes[(UINT)eSceneType::stage3_2] = new Stage3_2();
		_Scenes[(UINT)eSceneType::stage3_3] = new Stage3_3();
		_Scenes[(UINT)eSceneType::end] = new Stage_Ending();
		
		_Scenes[(UINT)eSceneType::Tool] = new ToolScene();

		for (auto scene : _Scenes) {
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}

		_ActiveScene = _Scenes[(UINT)eSceneType::Title];
	}

	void Mn::SceneManager::Update()
	{
		_ActiveScene->Update();
	}

	void Mn::SceneManager::Render(HDC hdc)
	{
		_ActiveScene->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		_ActiveScene->Destroy();
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
		Camera::Clear();
		_ActiveScene->OnExit();
		CollisionManager::Clear();
		_ActiveScene = _Scenes[(UINT)SceneType];
		_ActiveScene->OnEnter();
	}
	void SceneManager::SetDontDestroy(float hp,bool iscat,int idx)
	{
		_Hp = hp;
		_Iscat = iscat;
		_Item = idx;
	}
	float SceneManager::GetDontDestroyHP()
	{
		return _Hp;
	}
	bool SceneManager::GetDontDestroyCat()
	{
		return _Iscat;
	}
	int SceneManager::GetDontDestroyIdx()
	{
		return _Item;
	}
}