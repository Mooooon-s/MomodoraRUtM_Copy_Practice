#include "MnPlayScene.h"
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