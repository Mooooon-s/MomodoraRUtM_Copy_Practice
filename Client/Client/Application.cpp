#include "Application.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnInput.h"

namespace Mn {
	Application::Application()
		: _Hwnd(NULL)
		, _Hdc(NULL)
		, _ToolHwnd(NULL)
		, _ToolHdc(NULL)
		, _BackBuffer(NULL)
		, _BackHDC(NULL)
		, _Width(0)
		, _Height(0)
		, _Pos(Vector2::Zero)
	{
	}
	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd) 
	{
		_Hwnd = hwnd;
		_Hdc = GetDC(_Hwnd);
		_Width = 960;
		_Height = 720;

		//비트맵 해상도를 설정하기 위한 실제 윈도우 크기를 계산해준다.
		RECT rect = { 0,0,_Width,_Height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//윈도우 크기 변경 및 출력 설정
		SetWindowPos(hwnd, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);

		ShowWindow(hwnd, true);

		_BackBuffer = CreateCompatibleBitmap(_Hdc, _Width, _Height);
		_BackHDC = CreateCompatibleDC(_Hdc);

		HBITMAP defaultBitmap 
			= (HBITMAP)SelectObject(_BackHDC, _BackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initialize();
		Camera::Initiailize();
	}
	void Application::Run() 
	{
		Update();
		Render();
		SceneManager::Destroy();
	}

	//로직을 담당하는 역할
	void Application::Update()
	{
		Time::Update();
		Input::Updatae();
		Camera::Update();

		SceneManager::Update();
		CollisionManager::Update();
	}

	//그림을 그리는 역할
	void Application::Render()
	{
		//clear
		clear();

		Time::Render(_BackHDC);
		Input::Render(_BackHDC);
		SceneManager::Render(_BackHDC);
		Camera::Render(_BackHDC);
		BitBlt(_Hdc, 0, 0, _Width, _Height, _BackHDC, 0, 0, SRCCOPY);
	}
	void Application::clear()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(121, 121, 121));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_BackHDC, grayBrush);
		Rectangle(_BackHDC, -1, -1, 1602, 902);
		SelectObject(_BackHDC, oldBrush);
		DeleteObject(grayBrush);
	}
}