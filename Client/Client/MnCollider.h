#pragma once
#include "MnComponent.h"

namespace Mn
{
	class Collider : public Component
	{
	private:
		Vector2 _Pos;
		Vector2 _Center;
		Vector2 _Size;
		Vector2 _Scale;
	public:
		Collider();
		~Collider();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
		void Center(Vector2 center);
		void Size(Vector2 size);
		void Scale(Vector2 scale);
	public:
		Vector2 Pos() { return _Pos; }
		Vector2 Size() { return _Size; }
	};
}

