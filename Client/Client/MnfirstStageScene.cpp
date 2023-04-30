#include "MnfirstStageScene.h"
#include "MnBG.h"
#include "MnObject.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnTilePalatte.h"
#include "MnGround.h"
#include "MnKaho.h"
#include "MnMonkey.h"
#include "MnImpBomb.h"
#include "MnPlayerHpBar.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnVeiwPoint.h"
namespace Mn
{
	Kaho* firstStageScene::_kaho = nullptr;
	bool firstStageScene::_Scene = false;
	firstStageScene::firstStageScene()
		: Scene()
		, _KahoHuman(nullptr)
		, _KahoCat(nullptr)
		, _Portal(nullptr)
		, _PlayerHpBar(nullptr)
		, _ItemBox(nullptr)
	{
	}
	firstStageScene::~firstStageScene()
	{
	}
	void firstStageScene::Initialize()
	{
		SetName(L"Stage1_1");
		Scene::Initialize();
		object::Instantiate<BG>(eLayerType::BG);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(30.0f, 570.0f), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(30.0f, 570.0f), eLayerType::Player);
		_kaho = object::Instantiate<Kaho>(Vector2(30.0f, 570.0f), eLayerType::Player);
		object::Instantiate<Monkey>(Vector2(600.0f, 575.0f), eLayerType::Monster);
		object::Instantiate<ImpBomb>(Vector2(1601, 382), eLayerType::Monster);
		object::Instantiate<Ground>(Vector2::Zero, eLayerType::Ground);
		_VeiwPoint = object::Instantiate<VeiwPoint>(Vector2(480, 360), eLayerType::UI);
		_Portal = object::Instantiate<Portal>(Vector2(1700,600), eLayerType::Portal);
		_ItemBox = object::Instantiate<ItemBox>(Vector2(20.0f, 50.0f), eLayerType::UI);
		_PlayerHpBar = object::Instantiate<PlayerHpBar>(Vector2(100.0f, 50.0f),eLayerType::UI);
		_Portal->moveToScene(eSceneType::stage1_2);
		_kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void firstStageScene::Update()
	{
		if (_Scene)
		{
			SceneManager::LoadScene(_Portal->PortalScene());
		}
		Scene::Update();
	}
	void firstStageScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void firstStageScene::Release()
	{
		Scene::Release();
	}
	void firstStageScene::OnEnter()
	{
		TilePalatte::Load(L"Stage1_1");
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
		_PlayerHpBar->Hp(SceneManager::GetDontDestroyHP());
		_kaho->HP(SceneManager::GetDontDestroyHP());
		_kaho->IsCat(SceneManager::GetDontDestroyCat());
		_ItemBox->IdxNum(SceneManager::GetDontDestroyIdx());
	}
	void firstStageScene::OnExit()
	{
		float hp = _kaho->HP();
		bool iscat = _kaho->IsCat();
		int idx = _ItemBox->GetItemNum();
		SceneManager::SetDontDestroy(hp, iscat, idx);
		Camera::SetTarget(nullptr);
	}
}