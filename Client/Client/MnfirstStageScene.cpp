#include "MnfirstStageScene.h"
#include "MnBG.h"
#include "MnKaho.h"
#include "MnObject.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnArsonist.h"
#include "MnCath.h"
#include "MnGround.h"
#include "MnMonkey.h"
#include "MnLupiar.h"
#include "MnMagnolia.h"

namespace Mn
{
	Kaho* firstStageScene::_kaho = nullptr;
	firstStageScene::firstStageScene()
		:_KahoHuman(nullptr)
		, _KahoCat(nullptr)
	{
	}
	firstStageScene::~firstStageScene()
	{
	}
	void firstStageScene::Initialize()
	{
		SetName(L"BossScene");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(200.0f, 400.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(200.0f, 400.0f), eLayerType::Player);
		//object::Instantiate<Magnolia>(Vector2(200.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<Lupiar>(Vector2(300.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<Arsonist>(Vector2(400.0f, 400.0f), eLayerType::Monster);
		//object::Instantiate<Cath>(Vector2(500.0f, 400.0f), eLayerType::NPC);
		object::Instantiate<Monkey>(Vector2(600.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<Ground>(Vector2::Zero, eLayerType::Ground);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void firstStageScene::Update()
	{
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
		TilePalatte::Load(L"Arsonist_Boss_Map");
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
	}
	void firstStageScene::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}