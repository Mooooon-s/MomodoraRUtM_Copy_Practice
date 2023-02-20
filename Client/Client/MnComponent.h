#pragma once
#include"MnEntity.h"

namespace Mn
{
	class Component : public Entity
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	};
}

