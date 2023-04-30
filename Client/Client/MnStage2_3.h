#pragma once
#include "MnScene.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnItemBox.h"
#include "MnMapTrriger.h"
#include "MnVeiwPoint.h"
#include "MnResources.h"
namespace Mn
{
	class Sound;
	class Stage2_3 : public Scene
	{
	private:
		static bool		_Scene;
		static Kaho*	_Kaho;
		Kaho_Human*		_KahoHuman;
		Kaho_Cat*		_KahoCat;
		Portal*			_Portal;
		ItemBox*		_ItemBox;
		MapTrriger*		_MapTrriger;
		VeiwPoint*		_VeiwPoint;
		Sound*			_BGSound;
	public:
		Stage2_3();
		~Stage2_3();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnEnter() override;
		void OnExit() override;
	public:
		static Kaho* GetKaho() { return _Kaho; }
		static void	ChangeScene(bool scene) { _Scene = scene; }
		void StopSound(std::wstring name) { Resources::Find<Sound>(name)->Stop(true); }
	};
}

