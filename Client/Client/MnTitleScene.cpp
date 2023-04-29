#include "MnTitleScene.h"
#include "MnSceneManager.h"
#include "MnInput.h"
#include "MnTitleBG.h"
#include "MnTitleUI.h"
#include "MnTitle_Letter.h"
#include "MnObject.h"
#include "MnCamera.h"
#include "MnFadeInOut.h"
#include "MnSound.h"
#include "MnResources.h"

namespace Mn
{
	TitleScene::TitleScene()
		: Scene()
		, fadeInOut(nullptr)
		, _MainTheme(nullptr)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		SetName(L"TitleScene");
		Scene::Initialize();

		_MainTheme = Resources::Load<Sound>(L"Title_Theme", L"..\\Resources\\Sound\\BG\\title.wav");
		_MainTheme->Play(true);
		TitleBG* BackGround= object::Instantiate<TitleBG>(eLayerType::BG);
		TitleUI* TitleAnima= object::Instantiate<TitleUI>(eLayerType::UI);
		object::Instantiate<Title_Letter>(eLayerType::UI);
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Down)
		{
			Sound* Start = Resources::Load<Sound>(L"Start_Sound", L"..\\Resources\\Sound\\BG\\Start_Game.wav");
			Start->Play(false);
			_MainTheme->Stop(true);
			SceneManager::LoadScene(eSceneType::play);
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
		Camera::SetTarget(nullptr);
		Camera::CamReset();
	}
	void TitleScene::OnExit()
	{
		
	}
}