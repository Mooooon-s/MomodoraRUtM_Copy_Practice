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
		//��� ��ü ����
		BG* BackGround = new BG();
		AddGameObject(BackGround, eLayer::BG);

		//�÷��̾� ��ü ����
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