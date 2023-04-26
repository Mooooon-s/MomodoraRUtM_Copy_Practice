#pragma once
#include "MnScene.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnMapTrriger.h"
#include "MnLupiar.h"
#include "MnMagnolia.h"
#include "MnMagnoliaBoss.h"
namespace Mn
{
	class Stage3_3 : public Scene
	{
	private:
		static bool		_Scene;
		static Kaho*	_kaho;
		Kaho_Human*		_KahoHuman;
		Kaho_Cat*		_KahoCat;
		Portal*			_Portal;
		ItemBox*		_ItemBox;
		MapTrriger*		_Maptrriger;
		Magnolia*		_Mag;
		Lupiar*			_Lup;
		bool			_Page;
		MagnoliaBoss*	_MagBoss;

	public:
		Stage3_3();
		~Stage3_3();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnEnter() override;
		void OnExit() override;
	public:
		static Kaho* GetKaho() { return _kaho; }
		static void	ChangeScene(bool scene) { _Scene = scene; }
		void Page(bool page) { _Page = page; }
	};
}

