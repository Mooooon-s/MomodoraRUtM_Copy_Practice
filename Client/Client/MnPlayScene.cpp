#include "MnPlayScene.h"
#include "MnBG.h"
#include "MnMomodora.h"
#include "MnKaho.h"
#include "MnImp.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"
#include "MnArsonist.h"
#include "MnGround.h"
#include "MnInput.h"
#include "MnSceneManager.h"
#include "MnCamera.h"
#include "MnObject.h"
#include "MnCollisionManager.h"


namespace Mn 
{
	Kaho* PlayScene::_kaho = nullptr;
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
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_KahoHuman =object::Instantiate<Kaho_Human>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_kaho =object::Instantiate<Kaho>(Vector2(200.0f,400.0f),eLayerType::Player);
		object::Instantiate<Imp>(Vector2(100.0f, 400.0f),eLayerType::Monster);
		object::Instantiate<Arsonist>(Vector2(400.0f, 400.0f),eLayerType::Monster);
		object::Instantiate<Ground>(Vector2(0.0f, 500.0f), eLayerType::Ground);

		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
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
		Camera::SetTarget(_kaho->CameraTarget<GameObject>());
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster,true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
	}
	void PlayScene::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}