#pragma once
#include "MnEntity.h"
#include "MnGameObject.h"

namespace Mn
{
	class Layer : public Entity
	{
	private:
		std::vector<GameObject*> _GameObject;

	public:
		Layer();
		virtual ~Layer();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		void AddGameObject(GameObject* obj);
		std::vector<GameObject*>& GetGameObjects() { return _GameObject; }

	};
}
