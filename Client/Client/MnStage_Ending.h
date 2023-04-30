#pragma once
#include "MnScene.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnPlayerHpBar.h"
#include "MnVeiwPoint.h"
#include "MnMapTrriger.h"

namespace Mn
{
	class Stage_Ending : public Scene
	{
	private:
		static bool		_Scene;
		static Kaho*	_kaho;
		Portal*			_Portal;
		ItemBox*		_ItemBox;
		Kaho_Cat*		_KahoCat;
		VeiwPoint*		_VeiwPoint;
		Kaho_Human*		_KahoHuman;
		MapTrriger*		_MapTrriger;
		PlayerHpBar*	_PlayerHpBar;
	public:
		Stage_Ending();
		~Stage_Ending();
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
	};
}
