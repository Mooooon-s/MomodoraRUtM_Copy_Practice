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
namespace Mn
{
	Kaho* Stage2_2::_Kaho = nullptr;
	bool  Stage2_2::_Scene = false;
	Stage2_2::Stage2_2()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
	{
	}
	Stage2_2::~Stage2_2()
	{
	}
	void Stage2_2::Initialize()
	{
		SetName(L"Stage2_2");
		Scene::Initialize();
		_Kaho = object::Instantiate<Kaho>(Vector2(900, 300), eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(900, 300), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(900, 300), eLayerType::Player);
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
	}
	void Stage2_2::OnExit()
	{
		Camera::SetTarget(nullptr);
	}
}