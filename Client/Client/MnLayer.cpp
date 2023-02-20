#include"MnLayer.h"

namespace Mn {
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
		for (auto gameObj : _GameObject) {
			if (gameObj == nullptr)
				continue;
			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : _GameObject) {
			if (gameObj == nullptr)
				continue;

			gameObj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (auto gameObj : _GameObject) {
			if (gameObj == nullptr)
				continue;
			gameObj->Render(hdc);
		}
	}
	void Layer::Release()
	{
		for (auto gameObj : _GameObject) {
			if (gameObj == nullptr)
				continue;
			gameObj->Release();
		}
	}
	void Layer::AddGameObject(GameObject* obj)
	{
		if (obj == nullptr)
			return;
		_GameObject.push_back(obj);
	}
}