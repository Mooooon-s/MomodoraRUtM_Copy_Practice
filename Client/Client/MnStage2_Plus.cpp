#include "MnStage2_Plus.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnObject.h"
#include "MnGround.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnUnderGroundBG.h"
#include "MnPortal.h"
#include "MnInput.h"
#include "MnPlayerHpBar.h"
#include "MnItemBox.h"
#include "MnCath.h"
#include "MnArsonist.h"
#include "MnMapTrriger.h"
#include "MnGameObject.h"
#include "MnWall.h"
#include "MnVeiwPoint.h"
#include "MnSound.h"
#include "MnResources.h"
#include "MnCatPeasant.h"
#include "MnImpKnife.h"
#include "MnMonkey.h"


namespace Mn
{
	Kaho* Stage2_Plus::_kaho = nullptr;
	bool Stage2_Plus::_Scene = false;
	Stage2_Plus::Stage2_Plus()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
		, _VeiwPoint(nullptr)
	{
	}
	Stage2_Plus::~Stage2_Plus()
	{
	}
	void Stage2_Plus::Initialize()
	{
		SetName(L"Stage2_Plus");
		Scene::Initialize();
		object::Instantiate<UnderGroundBG>(eLayerType::BG);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(30, 770), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(30, 770), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(30, 770), eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(eLayerType::Ground);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		_Portal = object::Instantiate<Portal>(Vector2(1225, 300), eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(50, 700));
		_Portal->moveToScene(eSceneType::stage2_3);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		object::Instantiate<Monkey>(Vector2(890, 335), eLayerType::Monster);
		object::Instantiate<Monkey>(Vector2(790, 578), eLayerType::Monster);
		object::Instantiate<ImpKnife>(Vector2(339, 770), eLayerType::Monster);
		object::Instantiate<CatPeasant>(Vector2(563, 165), eLayerType::Monster);

	}
	void Stage2_Plus::Update()
	{
		if (_Scene)
			SceneManager::LoadScene(_Portal->PortalScene());
		Scene::Update();
	}
	void Stage2_Plus::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage2_Plus::Release()
	{
		Scene::Release();
	}
	void Stage2_Plus::OnEnter()
	{
		TilePalatte::Load(L"Stage2_Plus");
		Camera::SetTarget(_VeiwPoint);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::NPC, true);
		CollisionManager::SetLayer(eLayerType::Throws, eLayerType::NPC, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trriger, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Throws, eLayerType::Attack, true);
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
		SceneManager::SetWall(false);
	}
	void Stage2_Plus::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}