#include "MnStage3_3.h"
#include "MnObject.h"
#include "MnKaho.h"
#include "MnGround.h"
#include "MnPlayerHpBar.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnCamera.h"
#include "MnPortal.h"
#include "MnStage3BG.h"
#include "MnItemBox.h"

namespace Mn
{
	Kaho* Stage3_3::_kaho = nullptr;
	bool Stage3_3::_Scene = false;
	Stage3_3::Stage3_3()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
	{
	}
	Stage3_3::~Stage3_3()
	{
	}
	void Stage3_3::Initialize()
	{
		SetName(L"Stage3_3");
		Scene::Initialize();
		object::Instantiate<Stage3BG>(eLayerType::BG);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(60, 660), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(60, 660), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(60, 660), eLayerType::Player);
		object::Instantiate<Ground>(eLayerType::Ground);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage3_3::Update()
	{
		Scene::Update();
	}
	void Stage3_3::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage3_3::Release()
	{
		Scene::Release();
	}
	void Stage3_3::OnEnter()
	{
		TilePalatte::Load(L"Stage3_3");
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
	}
	void Stage3_3::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}