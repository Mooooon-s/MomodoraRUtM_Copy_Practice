#include "MnTitleScene.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnTitleBG.h"
#include "MnTitleUI.h"

namespace Mn
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		TitleBG* BackGround = new TitleBG;
		AddGameObject(BackGround, eLayerType::BG);

		TitleUI* TitleName = new TitleUI;
		AddGameObject(TitleName, eLayerType::UI);

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::MainMenu);
		}

		Scene::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}