#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Collider;
	class NpcMelee : public GameObject
	{
	private:
		Collider*	_Collider;
		float		_Timer;
	public:
		NpcMelee();
		~NpcMelee();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	};
}

