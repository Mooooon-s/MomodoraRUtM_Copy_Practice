#pragma once
#include "MnComponent.h"

namespace Mn
{
	class Collider : public Component
	{
	private:
		static UINT ColliderNumber;
		UINT mID;
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
	public:
		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
	public:
		void Center(Vector2 center) {_Center =center;}
		void Size(Vector2 size) { _Size = size; }
		void Scale(Vector2 scale) { _Scale = scale; }
		UINT GetID() { return mID; }
	public:
		Vector2 Pos() { return _Pos; }
		Vector2 Size() { return _Size; }
	};
}

