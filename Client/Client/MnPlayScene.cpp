#include "MnPlayScene.h"
#include "MnBG.h"
#include "MnPlayerHpBar.h"

#include "MnKaho.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"

#include "MnImp.h"
#include "MnArsonist.h"
#include "MnImpBomb.h"
#include "MnImpKnife.h"
#include "MnMonkey.h"

#include "MnGround.h"
#include "MnInput.h"
#include "MnSceneManager.h"
#include "MnCamera.h"
#include "MnObject.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnPortal.h"


namespace Mn 
{
	Kaho* PlayScene::_kaho = nullptr;
	bool PlayScene::_Scene = false;
	PlayScene::PlayScene()
		: _KahoHuman(nullptr)
		, _KahoCat(nullptr)
		, _portal(nullptr)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		SetName(L"PlayScene");
		Scene::Initialize();
		//배경 객체 생성
		object::Instantiate<BG>(eLayerType::BG);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f,50.0f),eLayerType::UI);
		//플레이어 객체 생성
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(500.0f, 300.0f), eLayerType::Player);
		_KahoHuman =object::Instantiate<Kaho_Human>(Vector2(500.0f, 300.0f), eLayerType::Player);
		_kaho =object::Instantiate<Kaho>(Vector2(200.0f,300.0f),eLayerType::Player);
		object::Instantiate<Ground>(Vector2::Zero, eLayerType::Ground);
		_portal=object::Instantiate<Portal>(Vector2(1600.0f, 270.0f),eLayerType::Portal);
		_portal->moveToScene(eSceneType::Stage1);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::P))
		{
			object::Instantiate<ImpKnife>(Vector2(700.0f, 200.0f), eLayerType::Monster);
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			object::Instantiate<ImpBomb>(Vector2(600.0f, 300.0f), eLayerType::Monster);
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{		
			object::Instantiate<Imp>(Vector2(500.0f, 300.0f), eLayerType::Monster);
		}
		if (Input::GetKeyDown(eKeyCode::U))
		{
			object::Instantiate<Monkey>(Vector2(500.0f, 300.0f), eLayerType::Monster);
		}
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		if (_Scene)
		{
			SceneManager::LoadScene(_portal->PortalScene());
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
		TilePalatte::Load(L"TestStage");
		Camera::SetTarget(_kaho->CameraTarget<GameObject>());
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster,true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
	}
	void PlayScene::OnExit()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, false);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, false);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, false);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, false);
		Camera::SetTarget(nullptr);
	}
}