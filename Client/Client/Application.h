#pragma once
#include"MnEngine.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnInput.h"

namespace Mn {
	class Application
	{
	private:
		HWND		_Hwnd;
		HDC			_Hdc;
		Vector2		_Pos;
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return _Hwnd; }

	};

}

