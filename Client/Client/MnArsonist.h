#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class Animator;
	class Arsonist : public GameObject
	{
	private:
		Image* _Image;
		Animator* _Animator;
	public:
		Arsonist();
		~Arsonist();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc)override;
		void Release()override;

	};
}

