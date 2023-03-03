#pragma once
#include "MnComponent.h"

namespace Mn
{
	class Transform : public Component
	{
	private:
		Vector2 _Pos;
		Vector2 _Size;
		Vector2 _Scale;
	public:
		Transform();
		~Transform();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void Size(Vector2 size) { _Size = size; }
		void Pos(Vector2 pos)   { _Pos = pos; }
		void Scale(Vector2 scale) { _Scale = scale; }
		Vector2 Pos(void)  { return _Pos; }
		Vector2 Size(void) { return _Size; }
		Vector2 Scale(void) { return _Scale; }
	};
}
