#include "MnPlayScene.h"
#include "MnBG.h"
#include "MnMomodora.h"
#include "MnKaho.h"
#include "MnImp.h"
#include "MnArsonist.h"
#include "MnInput.h"
#include "MnSceneManager.h"



namespace Mn 
{
	

	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		//배경 객체 생성
		BG* BackGround = new BG();
		AddGameObject(BackGround, eLayerType::BG);

		//플레이어 객체 생성
		//Momodora* momodora = new Momodora();
		//AddGameObject(momodora, eLayerType::Player);

		//Kaho_Cat* kahoCat = new Kaho_Cat();
		//AddGameObject(kahoCat, eLayerType::Player);

		//Kaho_Human* kahoHuman = new Kaho_Human();
		//AddGameObject(kahoHuman, eLayerType::Player);

		Kaho* kaho = new Kaho();
		AddGameObject(kaho, eLayerType::Player);

		Imp* imp = new Imp();
		AddGameObject(imp, eLayerType::Monster);

		Arsonist* arsonist = new Arsonist();
		AddGameObject(arsonist, eLayerType::Monster);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
	}
}