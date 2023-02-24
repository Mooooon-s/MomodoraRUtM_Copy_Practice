#include "MnMainMenuScene.h"
#include "MnSceneManager.h"
#include "MnMainMenuBG.h"
#include "MnInput.h"

namespace Mn
{
	MainMenuScene::MainMenuScene()
	{
	}
	MainMenuScene::~MainMenuScene()
	{
	}
	void MainMenuScene::Initialize()
	{
		MainMenuBG* mainMenuBG = new MainMenuBG();
		Scene::AddGameObject(mainMenuBG, eLayerType::BG);
		Scene::Initialize();
	}
	void MainMenuScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::play);
		}
		Scene::Update();
	}
	void MainMenuScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void MainMenuScene::Release()
	{
		Scene::Release();
	}
}