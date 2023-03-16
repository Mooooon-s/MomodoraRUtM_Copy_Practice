#pragma once
#include "MnEntity.h"
#include "MnComponent.h"

namespace Mn
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Death,
		};
	private:
		std::vector<Component*> _Components;
		eState _State;
	public:
		GameObject();
		virtual ~GameObject();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eState State() { return _State; }
		void State(eState state) { _State = state; }

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
