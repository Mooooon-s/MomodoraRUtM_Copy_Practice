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
namespace Mn
{
	Kaho* Stage2_1::_Kaho = nullptr;
	bool  Stage2_1::_Scene = false;
	Stage2_1::Stage2_1()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
	{
	}
	Stage2_1::~Stage2_1()
	{
	}
	void Stage2_1::Initialize()
	{
		SetName(L"Stage2_1");
		Scene::Initialize();
		_Kaho = object::Instantiate<Kaho>(Vector2(777,0),eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(777, 0),eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(777, 0),eLayerType::Player);
		object::Instantiate<Ground>(eLayerType::Ground);
		object::Instantiate<UnderGroundBG>(eLayerType::BG);
		_Portal = object::Instantiate<Portal>(Vector2(0,350),eLayerType::Portal);
		_Portal->GetComponent<Collider>()->Size(Vector2(10 * 3, 400));
		_Portal->moveToScene(eSceneType::stage2_2);
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
	}
	void Stage2_1::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}