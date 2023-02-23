#pragma once
#include"MnEntity.h"
#include "MnLayer.h"
namespace Mn
{
	class Scene : public Entity
	{
	private:
		std::vector<Layer> _Layers;
	public:
		Scene();
		virtual ~Scene();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnEnter();
		virtual void OnExit();
	public:
		void AddGameObject(GameObject* obj, eLayerType layer);
	};
}

