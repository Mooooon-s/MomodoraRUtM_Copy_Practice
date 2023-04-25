#include "MnStage_1_3.h"
#include "MnBG.h"
#include "MnObject.h"
#include "MnKaho.h"
#include "MnGround.h"
#include "MnPlayerHpBar.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnCamera.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnMapTrriger.h"
#include "MnImpKnife.h"
namespace Mn
{
	Kaho* Stage_1_3::_kaho = nullptr;
	bool Stage_1_3::_Scene = false;
	Stage_1_3::Stage_1_3()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
		, _MapTrriger(nullptr)
	{
	}
	Stage_1_3::~Stage_1_3()
	{
	}
	void Stage_1_3::Initialize()
	{
		SetName(L"Stage1_3");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(60, 660),eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(60, 660),eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(60,660),eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(eLayerType::Ground);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		_MapTrriger = object::Instantiate<MapTrriger>(Vector2(450,500),eLayerType::Trriger);
		_Portal = object::Instantiate<Portal>(Vector2(950,660),eLayerType::Portal);
		_Portal->moveToScene(eSceneType::stage1_Boss);
	}
	void Stage_1_3::Update()
	{
		if (_MapTrriger != nullptr && _MapTrriger->Trriger() == true)
		{
			object::Instantiate<ImpKnife>(Vector2(180, 400), eLayerType::Monster);
			object::Instantiate<ImpKnife>(Vector2(760, 400), eLayerType::Monster);
			_MapTrriger->State(GameObject::eState::Death);
			_MapTrriger = nullptr;
		}
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void Stage_1_3::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage_1_3::Release()
	{
		Scene::Release();
	}
	void Stage_1_3::OnEnter()
	{
		TilePalatte::Load(L"Stage1_3");
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trriger, true);
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage_1_3::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}