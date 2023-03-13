#pragma once
#include "MnGameObject.h"
#include "MnScene.h"
#include "MnSceneManager.h"
#include "MnTransform.h"

namespace Mn::object
{
	template<typename T>
	static inline T* Instantiate(eLayerType layer)
	{
		T* gameobj = new T();
		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(gameobj,layer);
		gameobj->Initialize();
		return gameobj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType layer)
	{
		T* gameobj = new T();
		Scene* scene = SceneManager::ActiveScene();
		scene->AddGameObject(gameobj, layer);
		gameobj->Initialize();
		gameobj->GameObject::GetComponent<Transform>()->Pos(pos);
		return gameobj;
	}

	static void Destory(GameObject* obj)
	{
		obj->State(GameObject::eState::Death);
	}

}