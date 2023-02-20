#pragma once
#include "MnEntity.h"
#include "MnComponent.h"

namespace Mn
{
	class GameObject : public Entity
	{
	private:
		std::vector<Component*> _Components;
	protected:
		Vector2		_Pos;
	public:
		GameObject();
		virtual ~GameObject();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		
	};
}
