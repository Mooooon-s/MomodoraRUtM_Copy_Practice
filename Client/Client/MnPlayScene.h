#pragma once
#include"MnScene.h"
#include "MnKaho.h"
#include "MnPortal.h"
#include "MnItemBox.h"
namespace Mn 
{
	class PlayScene :public Scene
	{
	private:
		static bool _Scene;
		static Kaho*	_kaho;
		Kaho_Human*		_KahoHuman;
		Kaho_Cat*		_KahoCat;
		Portal*			_portal;
		ItemBox*		_ItemBox;
	public:
		PlayScene();
		~PlayScene();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	public:
		void OnEnter() override;
		void OnExit() override;
	public:
		static Kaho* GetKaho() { return _kaho; }
		static void	ChangeScene(bool scene) { _Scene = scene; }
	};
}

