#include "MnTime.h"
#include "Application.h"

extern Mn::Application application;

namespace Mn 
{
	double Time::_DeltaTime = 0.0l;
	double Time::_Second = 0.0f;
	LARGE_INTEGER Time::_CpuFrequency = {};
	LARGE_INTEGER Time::_PrevFrequency = {};
	LARGE_INTEGER Time::_CurFrequency = {};
	
	void Time::Initialize()
	{
		//cpu 고유 진동수 1초에 몇번 진동하는지
		QueryPerformanceFrequency(&_CpuFrequency);

		//프로그램 처름 시작할때 진동수
		QueryPerformanceCounter(&_PrevFrequency);
	}

	void Time::Update()
	{
		//현재 한프레임이 지난 진동수
		QueryPerformanceCounter(&_CurFrequency);

		// 이전 진동수 - 현재 진동수
		double differnceFrequency = _CurFrequency.QuadPart - _PrevFrequency.QuadPart;

		//두 진동수의 차를 1초로 나누면 한 프레임에 걸린 시간이 나옴
		_DeltaTime = differnceFrequency / _CpuFrequency.QuadPart;
		_PrevFrequency.QuadPart = _CurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		_Second += _DeltaTime;

		if (_Second > 1.0) 
		{
			HWND hwnd = application.GetHwnd();
			wchar_t szFloat[50] = {};

			//프레임 계산
			float FPS = 1.0f / _DeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			SetWindowText(hwnd, szFloat);
			
			_Second = 0.0f;
		}
	}

}
