#pragma once
#include"MnEngine.h"


namespace Mn {
	class Application
	{
	private:
		HWND		_Hwnd;
		HDC			_Hdc;

		HBITMAP		_BackBuffer;
		HDC			_BackHDC;

		UINT		_Width;
		UINT		_Height;

		Vector2		_Pos;
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return _Hwnd; }
		HDC	 GetHdc()  { return _Hdc; }
		UINT Width() { return _Width; }
		UINT Height() { return _Height; }

	};

}

