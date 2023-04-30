#pragma once
#include "MnScene.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnItemBox.h"
namespace Mn
{
	class Sound;
	class Stage2_1 : public Scene
	{
	private:
		static bool		_Scene;
		static Kaho*	_Kaho;
		Kaho_Human*		_KahoHuman;
		Kaho_Cat*		_KahoCat;
		Portal*			_Portal;
		ItemBox*		_ItemBox;
		Sound*			_BGSound;
	public:
		Stage2_1();
		~Stage2_1();
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
	};
}

