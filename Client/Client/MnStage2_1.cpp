#include "MnStage2_1.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnObject.h"
#include "MnGround.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnUnderGroundBG.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnPlayerHpBar.h"
#include "MnBell.h"
namespace Mn
{
	Kaho* Stage2_1::_Kaho = nullptr;
	bool  Stage2_1::_Scene = false;
	Stage2_1::Stage2_1()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
		, _ItemBox(nullptr)
	{
	}
	Stage2_1::~Stage2_1()
	{
	}
	void Stage2_1::Initialize()
	{
		SetName(L"Stage2_1");
		Scene::Initialize();
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_Kaho = object::Instantiate<Kaho>(Vector2(777,0),eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(777, 0),eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(777, 0),eLayerType::Player);
		object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f), eLayerType::UI);
		object::Instantiate<Ground>(eLayerType::Ground);
		object::Instantiate<UnderGroundBG>(eLayerType::BG);
		_Portal = object::Instantiate<Portal>(Vector2(0,350),eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(10 * 3, 400));
		_Portal->moveToScene(eSceneType::stage2_2);
		Bell* bell = object::Instantiate<Bell>(Vector2(461,674),eLayerType::Ground);
		bell->BellNumber(2);
		_Kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage2_1::Update()
	{
		if (_Scene)
			SceneManager::LoadScene(_Portal->PortalScene());
		Scene::Update();
	}
	void Stage2_1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage2_1::Release()
	{
		Scene::Release();
	}
	void Stage2_1::OnEnter()
	{
		TilePalatte::Load(L"Stage2_1");
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		_Kaho->HP(SceneManager::GetDontDestroyHP());
		_Kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void Stage2_1::OnExit()
	{
		float hp = _Kaho->HP();
		bool iscat = _Kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}