#include "MnPlayScene.h"
#include "MnBG.h"
#include "MnMomodora.h"
#include "MnKaho.h"
#include "MnImp.h"
#include "MnArsonist.h"
#include "MnInput.h"
#include "MnSceneManager.h"
#include "MnCamera.h"
#include "MnObject.h"
#include "MnCollisionManager.h"


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
		Scene::Initialize();
		//배경 객체 생성
		object::Instantiate<BG>(eLayerType::BG);

		//플레이어 객체 생성
		object::Instantiate<Kaho>(Vector2(200.0f,400.0f),eLayerType::Player);
		object::Instantiate<Imp>(Vector2(100.0f, 400.0f),eLayerType::Monster);
		object::Instantiate<Arsonist>(Vector2(400.0f, 400.0f),eLayerType::Monster);
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster,true);
	}
	void PlayScene::OnExit()
	{
	}
}