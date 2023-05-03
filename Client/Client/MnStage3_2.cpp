#include "MnStage3_2.h"
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
#include "MnVeiwPoint.h"
#include "MnImpBomb.h"
#include "MnCatPeasant.h"

namespace Mn
{
	Kaho* Stage3_2::_kaho = nullptr;
	bool Stage3_2::_Scene = false;
	Stage3_2::Stage3_2()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
	{
	}
	Stage3_2::~Stage3_2()
	{
	}
	void Stage3_2::Initialize()
	{
		SetName(L"Stage3_2");
		Scene::Initialize();
		object::Instantiate<Stage3BG>(eLayerType::BG);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(60, 239), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(60, 239), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(60, 239), eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(eLayerType::Ground);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		_Portal = object::Instantiate<Portal>(Vector2(1880, 311), eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(50, 700));
		_Portal->moveToScene(eSceneType::stage3_3);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		object::Instantiate<ImpBomb>(Vector2(700,236), eLayerType::Monster);
		object::Instantiate<ImpBomb>(Vector2(1127,863), eLayerType::Monster);
		object::Instantiate<CatPeasant>(Vector2(1200, 236), eLayerType::Monster);
	}
	void Stage3_2::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void Stage3_2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage3_2::Release()
	{
		Scene::Release();
	}
	void Stage3_2::OnEnter()
	{
		TilePalatte::Load(L"Stage3_2");
		Camera::SetTarget(_VeiwPoint);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage3_2::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}