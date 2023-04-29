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
#include "MnInput.h"
#include "MnItemBox.h"
#include "MnMapTrriger.h"
#include "MnWall.h"
#include "MnVeiwPoint.h"
#include "MnSound.h"
#include "MnResources.h"

namespace Mn
{
	Kaho* Stage1_Boss::_kaho = nullptr;
	bool Stage1_Boss::_Scene = false;
	Stage1_Boss::Stage1_Boss()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
		, _MapTrriger(nullptr)
		, _BGSound(nullptr)
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
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(50.0f, 570.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(50.0f, 570.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(50.0f, 570.0f), eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(Vector2::Zero,eLayerType::Ground);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		_Portal = object::Instantiate<Portal>(Vector2(1440,900),eLayerType::Portal);
		_MapTrriger = object::Instantiate<MapTrriger>(Vector2(564,400),eLayerType::Trriger);
		_Portal->GetComponent<Collider>()->Size(Vector2(100*3,100));
		_Portal->moveToScene(eSceneType::stage2_1);
		_BGSound = Resources::Find<Sound>(L"ForestBGSound");
	}
	void Stage1_Boss::Update()
	{
		if (_MapTrriger != nullptr && _MapTrriger->Trriger() == true)
		{
			object::Instantiate<BigPlant>(Vector2(1200.0f, 570.0f), eLayerType::Monster);
			object::Instantiate<Wall>(Vector2(275, 0), eLayerType::Ground);
			object::Instantiate<Wall>(Vector2(1270, 0), eLayerType::Ground);
			_MapTrriger->State(GameObject::eState::Death);
			_MapTrriger = nullptr;
		}
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::stage2_3);
		}
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
		Camera::SetTarget(_VeiwPoint);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trriger, true);
		CollisionManager::SetLayer(eLayerType::Throws, eLayerType::Attack, true);
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
		SceneManager::SetWall(false);
	}
	void Stage1_Boss::OnExit()
	{
		_BGSound->Stop(true);
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}