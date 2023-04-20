#include "MnfirstStageScene.h"
#include "MnBG.h"
#include "MnObject.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnGround.h"
#include "MnKaho.h"
#include "MnMonkey.h"
#include "MnImpBomb.h"
#include "MnPlayerHpBar.h"
#include "MnPortal.h"
#include "MnItemBox.h"
namespace Mn
{
	Kaho* firstStageScene::_kaho = nullptr;
	bool firstStageScene::_Scene = false;
	firstStageScene::firstStageScene()
		:_KahoHuman(nullptr)
		, _KahoCat(nullptr)
		, _Portal(nullptr)
	{
	}
	firstStageScene::~firstStageScene()
	{
	}
	void firstStageScene::Initialize()
	{
		SetName(L"Stage1_1");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f),eLayerType::UI);
		object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(200.0f, 400.0f), eLayerType::Player);
		object::Instantiate<Monkey>(Vector2(600.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<ImpBomb>(Vector2(1601, 382), eLayerType::Monster);
		object::Instantiate<Ground>(Vector2::Zero, eLayerType::Ground);
		_Portal = object::Instantiate<Portal>(Vector2(1700,600), eLayerType::Portal);
		_Portal->moveToScene(eSceneType::stage1_2);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void firstStageScene::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void firstStageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void firstStageScene::Release()
	{
		Scene::Release();
	}
	void firstStageScene::OnEnter()
	{
		TilePalatte::Load(L"Stage1_1");
		Camera::SetTarget(_kaho->CameraTarget<GameObject>());
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
	}
	void firstStageScene::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}