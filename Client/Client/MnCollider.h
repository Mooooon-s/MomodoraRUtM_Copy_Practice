#pragma once
#include "MnComponent.h"

namespace Mn
{
	class Collider : public Component
	{
	private:
		static UINT ColliderNumber;
		UINT		_ID;
		UINT		_CollisionCount;
		Vector2		_Pos;
		Vector2		_Center;
		Vector2		_Size;
		Vector2		_Scale;
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
	public:
		Vector2 Center() { return _Center; }
		Vector2 Pos() { return _Pos; }
		Vector2 Size() { return _Size; }
		UINT GetID() { return _ID; }
	};
}

