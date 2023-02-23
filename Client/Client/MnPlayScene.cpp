#include "MnPlayScene.h"
#include "MnBG.h"
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
		AddGameObject(BackGround, eLayer::BG);

		//플레이어 객체 생성
		Momodora* momodora = new Momodora();
		AddGameObject(momodora, eLayer::Player);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eScene::Title);
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