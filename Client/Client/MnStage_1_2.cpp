#include "MnStage_1_2.h"
#include "MnCamera.h"
#include "MnComponent.h"
#include "MnObject.h"
#include "MnGround.h"
#include "MnBG.h"
#include "MnPlayerHpBar.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnImpKnife.h"
#include "MnImp.h"
#include "MnItemBox.h"
#include "MnVeiwPoint.h"

namespace Mn
{
	Kaho* Stage_1_2::_kaho = nullptr;
	bool Stage_1_2::_Scene = false;
	Stage_1_2::Stage_1_2()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
		, _PlayerHpBar(nullptr)
	{
	}
	Stage_1_2::~Stage_1_2()
	{
	}
	void Stage_1_2::Initialize()
	{
		SetName(L"Stage1_2");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(50.0f, 240.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(50.0f, 240.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(50.0f, 240.0f), eLayerType::Player);

		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_PlayerHpBar = object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		_Portal= object::Instantiate<Portal>(Vector2(950, 770), eLayerType::Portal);
		object::Instantiate<ImpKnife>(Vector2(630, 238), eLayerType::Monster);
		object::Instantiate<Imp>(Vector2(600, 700),eLayerType::Monster);
		_Portal->moveToScene(eSceneType::stage1_3);
		object::Instantiate<Ground>(eLayerType::Ground);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage_1_2::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void Stage_1_2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage_1_2::Release()
	{
		Scene::Release();
	}
	void Stage_1_2::OnEnter()
	{
		TilePalatte::Load(L"Stage1_2");
		Camera::SetTarget(_VeiwPoint);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Throws, eLayerType::Attack, true);
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
		_PlayerHpBar->Hp(SceneManager::GetDontDestroyHP());
	}
	void Stage_1_2::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}