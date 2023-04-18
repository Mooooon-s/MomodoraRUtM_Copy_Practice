#include "MnStage1_Boss.h"
#include "MnCollisionManager.h"
#include "MnCamera.h"
#include "MnKaho.h"
#include "MnBG.h"
#include "MnPlayerHpBar.h"
#include "MnTilePalatte.h"
#include "MnGround.h"
namespace Mn
{
	bool Stage1_Boss::_Scene = false;
	Kaho* Stage1_Boss::_kaho = nullptr;
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
	}
	void Stage1_Boss::Update()
	{
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