#pragma once
#include "MnEntity.h"
#include "MnComponent.h"

namespace Mn
{
	class GameObject : public Entity
	{
	private:
		std::vector<Component*> _Components;
	public:
		GameObject();
		virtual ~GameObject();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		template<typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->Type();
			_Components[compType] = comp;
			comp->Owner(this);

			return comp;
		}
		
		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : _Components)
			{
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);
			}
			return nullptr;
		}
	};
}
