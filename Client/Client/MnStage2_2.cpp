#include "MnStage2_2.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnObject.h"
#include "MnGround.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnUnderGroundBG.h"
#include "MnPortal.h"
#include "MnPlayerHpBar.h"
#include "MnItemBox.h"
#include "MnCatPeasant.h"
namespace Mn
{
	Kaho* Stage2_2::_Kaho = nullptr;
	bool  Stage2_2::_Scene = false;
	Stage2_2::Stage2_2()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
	{
	}
	Stage2_2::~Stage2_2()
	{
	}
	void Stage2_2::Initialize()
	{
		SetName(L"Stage2_2");
		Scene::Initialize();
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_Kaho = object::Instantiate<Kaho>(Vector2(900, 300), eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(900, 300), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(900, 300), eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<CatPeasant>(Vector2(159,300),eLayerType::Monster);
		object::Instantiate<CatPeasant>(Vector2(800,674),eLayerType::Monster);
		object::Instantiate<Ground>(eLayerType::Ground);
		object::Instantiate<UnderGroundBG>(eLayerType::BG);
		_Portal = object::Instantiate<Portal>(Vector2(900,600),eLayerType::Portal);
		_Portal->moveToScene(eSceneType::stage2_3);
		_Kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage2_2::Update()
	{
		if (_Scene)
			SceneManager::LoadScene(_Portal->PortalScene());
		Scene::Update();
	}
	void Stage2_2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage2_2::Release()
	{

		Scene::Release();
	}
	void Stage2_2::OnEnter()
	{
		TilePalatte::Load(L"Stage2_2");
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Throws, eLayerType::Attack, true);
		_Kaho->HP(SceneManager::GetDontDestroyHP());
		_Kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage2_2::OnExit()
	{
		float hp = _Kaho->HP();
		bool iscat = _Kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}