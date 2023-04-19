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
namespace Mn
{
	Kaho* Stage2_3::_Kaho = nullptr;
	bool  Stage2_3::_Scene = false;
	Stage2_3::Stage2_3()
		: Scene()
		, _KahoCat(nullptr)
		, _KahoHuman(nullptr)
		, _Portal(nullptr)
	{
	}
	Stage2_3::~Stage2_3()
	{
	}
	void Stage2_3::Initialize()
	{
		SetName(L"Stage2_3");
		Scene::Initialize();
		_Kaho = object::Instantiate<Kaho>(Vector2(100, 600), eLayerType::Player);
		_KahoCat = object::Instantiate<Kaho_Cat>(Vector2(100, 600), eLayerType::Player);
		_KahoHuman = object::Instantiate<Kaho_Human>(Vector2(100, 600), eLayerType::Player);
		object::Instantiate<Ground>(eLayerType::Ground);
		object::Instantiate<UnderGroundBG>(eLayerType::BG);
		_Kaho->GetCatHunam(_KahoCat, _KahoHuman);
	}
	void Stage2_3::Update()
	{
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
		Camera::SetTarget(nullptr);
		Camera::CamReset(1.5f);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
		CollisionManager::SetLayer(eLayerType::Attack, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Throws, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Throws, true);
	}
	void Stage2_3::OnExit()
	{
	}
}