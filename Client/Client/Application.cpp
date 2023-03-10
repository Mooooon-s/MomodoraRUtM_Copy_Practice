#include "Application.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnInput.h"

namespace Mn {
	Application::Application() 
		:_Hwnd(NULL)
		,_Hdc(NULL)
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
		SetWindowPos(hwnd, nullptr, 100, 50
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
		Rectangle(_BackHDC,-1, -1, 1602, 902);

		Time::Render(_BackHDC);
		Input::Render(_BackHDC);
		SceneManager::Render(_BackHDC);

		BitBlt(_Hdc, 0, 0, _Width, _Height, _BackHDC, 0, 0, SRCCOPY);
	}
}