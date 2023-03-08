#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Animator;
	class Arrow : public GameObject
	{
	private:
		Animator* _Animator;
	public:
		Arrow();
		~Arrow();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	};
}

