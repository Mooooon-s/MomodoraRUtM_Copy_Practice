#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Collider;
	class MapTrriger : public GameObject
	{
	private:
		Collider*	_Collider;
		bool		_Trriger;
	public:
		MapTrriger();
		~MapTrriger();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		virtual void OnCollisionEnter(class Collider* other);
	public:
		bool Trriger() { return _Trriger; }
	};
}
