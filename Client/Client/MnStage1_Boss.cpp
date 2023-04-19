#include "MnStage1_Boss.h"
#include "MnBG.h"
#include "MnObject.h"
#include "MnBigPlant.h"
#include "MnKaho.h"
#include "MnGround.h"
#include "MnPlayerHpBar.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnCamera.h"
#include "MnPortal.h"

namespace Mn
{
	Kaho* Stage1_Boss::_kaho = nullptr;
	bool Stage1_Boss::_Scene = false;
	Stage1_Boss::Stage1_Boss()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
	{
	}
	Stage1_Boss::~Stage1_Boss()
	{
	}
	void Stage1_Boss::Initialize()
	{
		SetName(L"Stage1_Boss");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(200.0f, 400.0f), eLayerType::Player);
		object::Instantiate<Ground>(Vector2::Zero,eLayerType::Ground);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		object::Instantiate<BigPlant>(Vector2(1200, 400), eLayerType::Monster);
		_Portal = object::Instantiate<Portal>(Vector2(1500,900),eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(100*3,100));
		_Portal->moveToScene(eSceneType::stage2_1);
	}
	void Stage1_Boss::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void Stage1_Boss::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage1_Boss::Release()
	{
		Scene::Release();
	}
	void Stage1_Boss::OnEnter()
	{
		TilePalatte::Load(L"Stage1_Boss");
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
	void Stage1_Boss::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}