#pragma once
#include"MnEntity.h"

namespace Mn
{
	class Component : public Entity
	{
	private:
		const eComponentType _Type;
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
	};
}

