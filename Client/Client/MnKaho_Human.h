#pragma once
#include "MnGameObject.h"
#include "MnImage.h"

namespace Mn
{
	class Animator;
	class Kaho_Human : public GameObject
	{
	private:
		//static Vector2		_Pos;
		Animator* _Animator;
		Image* _Image;
		int					_col;
		int					_row;
	public:
		Kaho_Human();
		~Kaho_Human();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	};
}

