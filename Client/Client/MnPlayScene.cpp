#include "MnPlayScene.h"
#include "MnResources.h"
#include "MnBG.h"


namespace Mn 
{
	

	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		//배경 객체 생성
		BG* BackGround = new BG();
		AddGameObject(BackGround, eLayer::BG);

		//플레이어 객체 생성
		Momodora* momodora = new Momodora();
		AddGameObject(momodora, eLayer::Player);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
}