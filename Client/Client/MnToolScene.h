#pragma once
#include "MnScene.h"

namespace Mn
{
	class ToolScene : public Scene
	{
	private:
		static HDC _Tilehdc;
		static HBITMAP _TileBitmap;
	public:
		ToolScene();
		~ToolScene();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;

		static void TBitmap(HBITMAP bitmap) { _TileBitmap= bitmap; }
		static HBITMAP TBitmap(void) { return _TileBitmap; }

		static void THdc(HDC hdc) { _Tilehdc = hdc; }
		static HDC THdc(void) { return _Tilehdc; }
	};
}

