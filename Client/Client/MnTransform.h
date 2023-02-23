#pragma once
#include "MnComponent.h"

namespace Mn
{
	class Transform : public Component
	{
	private:
		Vector2 _Pos;
		Vector2 _Size;
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
		Vector2 Pos(void)  { return _Pos; }
		Vector2 Size(void) { return _Size; }
	};
}
