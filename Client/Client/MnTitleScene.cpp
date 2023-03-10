#include "MnTitleScene.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnTitleBG.h"
#include "MnTitleUI.h"
#include "MnTitle_Letter.h"
#include "MnObject.h"
#include "MnCamera.h"

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
		//TitleBG* BackGround = new TitleBG;
		//AddGameObject(BackGround, eLayerType::BG);
		//TitleUI* TitleAnima = new TitleUI;
		//AddGameObject(TitleAnima, eLayerType::UI);
		//Title_Letter* TitleName = new Title_Letter;
		//AddGameObject(TitleName, eLayerType::UI);
		//Camera::SetTarget(BackGround);
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
	}
	void TitleScene::OnExit()
	{
	}
}