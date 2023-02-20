#include "MnScene.h"


namespace Mn
{
	Scene::Scene()
	{
		_Layers.resize((UINT)eLayer::Max);
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer& layer : _Layers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : _Layers)
		{
			layer.Update();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : _Layers)
		{
			layer.Render(hdc);
		}
	}
	void Scene::Release()
	{
		for (Layer& layer : _Layers)
		{
			layer.Release();
		}
	}
	void Scene::AddGameObject(GameObject* obj, eLayer layer)
	{
		_Layers[(UINT)layer].AddGameObject(obj);
	}
}