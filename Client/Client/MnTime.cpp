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
		//cpu ���� ������ 1�ʿ� ��� �����ϴ���
		QueryPerformanceFrequency(&_CpuFrequency);

		//���α׷� ó�� �����Ҷ� ������
		QueryPerformanceCounter(&_PrevFrequency);
	}

	void Time::Update()
	{
		//���� ���������� ���� ������
		QueryPerformanceCounter(&_CurFrequency);

		// ���� ������ - ���� ������
		double differnceFrequency = _CurFrequency.QuadPart - _PrevFrequency.QuadPart;

		//�� �������� ���� 1�ʷ� ������ �� �����ӿ� �ɸ� �ð��� ����
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

			//������ ���
			float FPS = 1.0f / _DeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			SetWindowText(hwnd, szFloat);
			
			_Second = 0.0f;
		}
	}

}
