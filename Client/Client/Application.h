#pragma once
#include"MnEngine.h"


namespace Mn {
	class Application
	{
	private:
		HWND		_Hwnd;
		HDC			_Hdc;
		HWND		_ToolHwnd;
		HDC			_ToolHdc;
		HBITMAP		_BackBuffer;
		HDC			_BackHDC;
		UINT		_Width;
		UINT		_Height;
		Vector2		_Pos;
	public:
		Application();
		~Application();
	public:
		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();
	public:
		HWND GetHwnd() { return _Hwnd; }
		HWND GetToolHwnd() { return _ToolHwnd; }
		HDC	 GetHdc()  { return _Hdc; }
		HDC	 GetToolHdc() { return _ToolHdc; }
		UINT Width() { return _Width; }
		UINT Height() { return _Height; }
		void SetToolHwnd(HWND hwnd){ _ToolHwnd = hwnd; }
	private:
		void clear();
	};

}

