#include "MnStage3_obstacle.h"
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
#include "MnBell.h"
#include "MnSound.h"
#include "MnObstacle.h"
#include "MnCatPeasant.h"
namespace Mn
{
	Kaho* Stage3_obstacle::_Kaho = nullptr;
	bool  Stage3_obstacle::_Scene = false;
	Stage3_obstacle::Stage3_obstacle()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
	{
	}
	Stage3_obstacle::~Stage3_obstacle()
	{
	}
	void Stage3_obstacle::Initialize()
	{
		SetName(L"Stage3_Obstacle");
		Scene::Initialize();
		object::Instantiate<Stage3BG>(eLayerType::BG);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_Kaho = object::Instantiate<Kaho>(Vector2(77, 623), eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(77, 623), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(77, 623), eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(eLayerType::Ground);
		_Portal = object::Instantiate<Portal>(Vector2(2350, 100), eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(10, 600));
		_Portal->moveToScene(eSceneType::stage3_2);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		object::Instantiate<CatPeasant>(Vector2(100, 200), eLayerType::Monster);
		object::Instantiate<CatPeasant>(Vector2(2200, 200), eLayerType::Monster);
		for (int i = 0; i < 17; i++)
		{
			object::Instantiate<Obstacle>(Vector2(1114+(i*45), 300), eLayerType::Monster);
		}
		_Kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage3_obstacle::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void Stage3_obstacle::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage3_obstacle::Release()
	{
		Scene::Release();
	}
	void Stage3_obstacle::OnEnter()
	{
		TilePalatte::Load(L"Stage3_1_1");
		Camera::SetTarget(_VeiwPoint);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Trriger, true);
		_Kaho->HP(SceneManager::GetDontDestroyHP());
		_Kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage3_obstacle::OnExit()
	{
		float hp = _Kaho->HP();
		bool iscat = _Kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}