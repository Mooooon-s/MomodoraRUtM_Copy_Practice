#include "MnTitleScene.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnTitleBG.h"
#include "MnTitleUI.h"
#include "MnTitle_Letter.h"
#include "MnObject.h"
#include "MnCamera.h"
#include "MnFadeInOut.h"

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
		Scene::Initialize();

		TitleBG* BackGround= object::Instantiate<TitleBG>(eLayerType::BG);
		TitleUI* TitleAnima= object::Instantiate<TitleUI>(eLayerType::UI);
		object::Instantiate<Title_Letter>(eLayerType::UI);
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
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{
		Camera::CamReset();
	}
	void TitleScene::OnExit()
	{
		
	}
}