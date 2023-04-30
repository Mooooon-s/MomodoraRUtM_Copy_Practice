#include "MnStage_Ending.h"
#include "MnBG.h"
#include "MnObject.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnGround.h"
#include "MnKaho.h"
#include "MnPlayerHpBar.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnVeiwPoint.h"
#include "MnMapTrriger.h"
#include "MnSound.h"
#include "MnResources.h"

namespace Mn
{
	Kaho* Stage_Ending::_kaho = nullptr;
	bool Stage_Ending::_Scene = false;
	Stage_Ending::Stage_Ending()
		: Scene()
		, _KahoHuman(nullptr)
		, _KahoCat(nullptr)
		, _Portal(nullptr)
		, _PlayerHpBar(nullptr)
		, _ItemBox(nullptr)
		, _VeiwPoint(nullptr)
		, _MapTrriger(nullptr)
	{
	}
	Stage_Ending::~Stage_Ending()
	{
	}
	void Stage_Ending::Initialize()
	{
		SetName(L"Ending");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(30.0f, 675.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(30.0f, 675.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(30.0f, 675.0f), eLayerType::Player);
		object::Instantiate<Ground>(Vector2::Zero, eLayerType::Ground);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		_Portal = object::Instantiate<Portal>(Vector2(1700, 600), eLayerType::Portal);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_PlayerHpBar = object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		_MapTrriger = object::Instantiate<MapTrriger>(Vector2(780.0f, 500.0f), eLayerType::Trriger);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
		Sound* BGSound = Resources::Load<Sound>(L"Ending_Sound", L"..\\Resources\\Sound\\BG\\forest_ambiance2.wav");
		BGSound->Play(true);
	}
	void Stage_Ending::Update()
	{
		if (_MapTrriger != nullptr && _MapTrriger->Trriger() == true)
		{
			Camera::Camtype(2);
			Camera::CamReset();
			_MapTrriger->State(GameObject::eState::Death);
			_MapTrriger = nullptr;
		}
		Scene::Update();
	}
	void Stage_Ending::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage_Ending::Release()
	{
		Scene::Release();
	}
	void Stage_Ending::OnEnter()
	{
		TilePalatte::Load(L"Ending");
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
		_PlayerHpBar->Hp(SceneManager::GetDontDestroyHP());
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage_Ending::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}