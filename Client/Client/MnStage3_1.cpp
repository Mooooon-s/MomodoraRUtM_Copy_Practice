#include "MnStage3_1.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnObject.h"
#include "MnGround.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnUnderGroundBG.h"
#include "MnPortal.h"
#include "MnStage3BG.h"
#include "MnPlayerHpBar.h"
#include "MnItemBox.h"
namespace Mn
{
	Kaho* Stage3_1::_Kaho = nullptr;
	bool  Stage3_1::_Scene = false;
	Stage3_1::Stage3_1()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
	{
	}
	Stage3_1::~Stage3_1()
	{
	}
	void Stage3_1::Initialize()
	{
		SetName(L"Stage3_1");
		Scene::Initialize();
		object::Instantiate<Stage3BG>(eLayerType::BG);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_Kaho = object::Instantiate<Kaho>(Vector2(100, 700), eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(100, 700), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(100, 700), eLayerType::Player);
		object::Instantiate<Ground>(eLayerType::Ground);
		_Portal = object::Instantiate<Portal>(Vector2(900,0),eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(10,600));
		_Portal->moveToScene(eSceneType::stage3_2);
		_Kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage3_1::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void Stage3_1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage3_1::Release()
	{
		Scene::Release();
	}
	void Stage3_1::OnEnter()
	{
		TilePalatte::Load(L"Stage3_1");
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
	}
	void Stage3_1::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}