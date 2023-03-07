#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Kaho_Cat : public GameObject
	{
	private:
		//static Vector2	_Pos;
		Animator*		_Animator;
	public:
		Kaho_Cat();
		~Kaho_Cat();
	public:
		 void Initialize()override;
		 void Update()override;
		 void Render(HDC hdc)override;
		 void Release() override;

	};
}

