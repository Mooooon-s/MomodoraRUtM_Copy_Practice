#include "MnTitleScene.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnTitleBG.h"

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

		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::play);
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