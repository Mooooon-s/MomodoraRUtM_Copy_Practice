#pragma once
#include "MnGameObject.h"
#include "MnKaho_Human.h"
#include "MnKaho_Cat.h"

namespace Mn
{
	class Kaho : public GameObject
	{
	private:
		Kaho_Human*		_KahoHuman;
		Kaho_Cat*		_KahoCat;
		bool			_bIsCat;
	public:
		Kaho();
		~Kaho();
	public:
		void Initialize()override;
		void Update()override;
		void Render(HDC hdc)override;
		void Release() override;
	public:
		virtual void KahoInitialize();
		virtual void KahoUpdate();
		virtual void KahoRender(HDC hdc);
		virtual void KahoRelease();
	};
}

