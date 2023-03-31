#pragma once
#include"MnEntity.h"

namespace Mn
{
	class GameObject;
	class Component : public Entity
	{
	private:
		const eComponentType	_Type;
		GameObject*				_Owner;
	public:
		Component(eComponentType Type);
		~Component();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		eComponentType Type() { return _Type; }
		GameObject* Owner(void) { return _Owner; }
		void Owner(GameObject* owner) { _Owner = owner; }
	};
}

