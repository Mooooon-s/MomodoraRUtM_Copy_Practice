#include "MnStage2_3.h"
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
namespace Mn
{
	Kaho* Stage2_3::_Kaho = nullptr;
	bool  Stage2_3::_Scene = false;
	Stage2_3::Stage2_3()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
		, _MapTrriger(nullptr)
	{
	}
	Stage2_3::~Stage2_3()
	{
	}
	void Stage2_3::Initialize()
	{
		SetName(L"Stage2_3");
		Scene::Initialize();
		object::Instantiate<UnderGroundBG>(eLayerType::BG);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_Kaho = object::Instantiate<Kaho>(Vector2(51, 600), eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(51, 600), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(51, 600), eLayerType::Player);
		_Portal = object::Instantiate<Portal>(Vector2(1367,550),eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(100, 300));
		_Portal->moveToScene(eSceneType::stage3_1);
		object::Instantiate<Ground>(eLayerType::Ground);
		_MapTrriger = object::Instantiate<MapTrriger>(Vector2(480,500),eLayerType::Trriger);
		_Kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage2_3::Update()
	{
		if (_MapTrriger!=nullptr && _MapTrriger->Trriger() == true)
		{
			object::Instantiate<Arsonist>(Vector2(1287, 670), eLayerType::Monster);
			object::Instantiate<Cath>(Vector2(1186, 670), eLayerType::NPC);
			_MapTrriger->State(GameObject::eState::Death);
			_MapTrriger = nullptr;
		}
		if (_Scene)
			SceneManager::LoadScene(_Portal->PortalScene());
		Scene::Update();
	}
	void Stage2_3::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage2_3::Release()
	{
		Scene::Release();
	}
	void Stage2_3::OnEnter()
	{
		TilePalatte::Load(L"Stage2_3");
		Camera::SetTarget(_Kaho->CameraTarget<GameObject>());
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::NPC, true);
		CollisionManager::SetLayer(eLayerType::Throws, eLayerType::NPC, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trriger, true);
		_Kaho->HP(SceneManager::GetDontDestroyHP());
		_Kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage2_3::OnExit()
	{
		float hp = _Kaho->HP();
		bool iscat = _Kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}