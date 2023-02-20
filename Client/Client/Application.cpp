#include "Application.h"

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

		Time::Initialize();
		Input::Initialize();
		SceneManager::Initialize();
	}
	void Application::Run() 
	{
		Update();
		Render();
	}

	//로직을 담당하는 역할
	void Application::Update()
	{
		Time::Update();
		Input::Updatae();
		SceneManager::Update();

	}

	//그림을 그리는 역할
	void Application::Render()
	{
		Time::Render(_Hdc);
		Input::Render(_Hdc);
		SceneManager::Render(_Hdc);
	}
}