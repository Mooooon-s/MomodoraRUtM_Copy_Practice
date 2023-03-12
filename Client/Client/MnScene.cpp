#include "MnScene.h"


namespace Mn
{
	Scene::Scene()
	{
		_Layers.resize((UINT)eLayerType::Max);
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
	void Scene::Destroy()
	{
		std::vector<GameObject*> deleteGameObjects = {};
		for (Layer& layer : _Layers)
		{
			std::vector<GameObject*>& gameobjects = layer.GetGameObjects();

			for (std::vector<GameObject*>::iterator iter = gameobjects.begin(); iter != gameobjects.end();)
			{
				if ((*iter)->State() == GameObject::eState::Death)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameobjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}

		for (GameObject* deathobj : deleteGameObjects)
		{
			delete deathobj;
			deathobj = nullptr;
		}
	}
	void Scene::Release()
	{
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		_Layers[(UINT)layer].AddGameObject(obj);
	}
	std::vector<GameObject*>& Scene::GetGameObject(eLayerType layer)
	{
		return _Layers[(UINT)layer].GetGameObjects();
	}
}