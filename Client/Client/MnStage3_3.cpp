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

#include "MnMagnolia.h"
#include "MnLupiar.h"
#include "MnMagnoliaBoss.h"

#include "MnMapTrriger.h"
#include "MnWall.h"
#include "MnSound.h"
#include "MnResources.h"
namespace Mn
{
	Kaho* Stage3_3::_kaho = nullptr;
	bool Stage3_3::_Scene = false;
	Stage3_3::Stage3_3()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
		, _Maptrriger(nullptr)
		, _Mag(nullptr)
		, _Lup(nullptr)
		, _MagBoss(nullptr)
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
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(60, 660), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(60, 660), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(60, 660), eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(eLayerType::Ground);
		_Maptrriger = object::Instantiate<MapTrriger>(Vector2(400,500), eLayerType::Trriger);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		_BGSound = Resources::Load<Sound>(L"Boss3_BG", L"..\\Resources\\Sound\\BG\\boss7_Lupiar.wav");
		_Portal = object::Instantiate<Portal>(Vector2(960, 660), eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(100 * 3, 100));
		_Portal->moveToScene(eSceneType::end);
	}
	void Stage3_3::Update()
	{
		if (_Maptrriger!=nullptr && _Maptrriger->Trriger())
		{
			object::Instantiate<Wall>(Vector2(0, 0), eLayerType::Ground);
			object::Instantiate<Wall>(Vector2(900, 0), eLayerType::Ground);
			_Maptrriger->State(GameObject::eState::Death);
			_Maptrriger = nullptr;
			_Lup = object::Instantiate<Lupiar>(Vector2(600, 660), eLayerType::Monster);
			_Mag = object::Instantiate<Magnolia>(Vector2(157, 800), eLayerType::Monster);
			Resources::Find<Sound>(L"Stage3_BGSound")->Stop(true);
			_BGSound->Play(true);
		}
		if (_Page == true && _MagBoss==nullptr)
		{
			_Mag->Done();
		}
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trriger, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
		SceneManager::SetWall(false);
	}
	void Stage3_3::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}