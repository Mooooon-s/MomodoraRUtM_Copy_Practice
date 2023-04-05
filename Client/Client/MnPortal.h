#pragma once
#include "MnCollider.h"
#include "MnGameObject.h"

namespace Mn
{
	class Portal :public GameObject
	{
	private:
		Collider* _Collider;
		eSceneType _Scene;
	public:
		Portal();
		~Portal();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	public:
		void moveToScene(eSceneType scene) { _Scene = scene; }
		eSceneType PortalScene() { return _Scene; }
	};
}

