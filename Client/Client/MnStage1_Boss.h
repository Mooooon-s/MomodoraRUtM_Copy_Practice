#pragma once
#include "MnScene.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnItemBox.h"
namespace Mn
{
	class Stage1_Boss : public Scene
	{
	private:
		static bool		_Scene;
		static Kaho*	_kaho;
		Kaho_Human*		_KahoHuman;
		Kaho_Cat*		_KahoCat;
		Portal*			_Portal;
		ItemBox*		_ItemBox;
	public:
		Stage1_Boss();
		~Stage1_Boss();
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
