#pragma once
#include "MnGameObject.h"

namespace Mn
{
	class Kaho_Cat;
	class Kaho_Human;
	class Kaho : public GameObject
	{
	private:
		bool			_bIsCat;
		Vector2			_Pos;
		Kaho_Cat*		kahoCat;
		Kaho_Human*		kahoHuman;
	public:
		Kaho();
		~Kaho();
	public:
		void Initialize()override;
		void Update()override;
		void Render(HDC hdc)override;
		void Release() override;
	};
}

