#include "MnSoundManager.h"
#include "Application.h"

extern Mn::Application application;

namespace Mn
{
	LPDIRECTSOUND8 SoundManager::_SoundDevice;

	bool SoundManager::Initialize()
	{
		if (FAILED(DirectSoundCreate8(NULL, &_SoundDevice, NULL)))
		{
			MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		// ���� ����̽� �������� ����.
		HWND hWnd = application.GetHwnd();
		if (FAILED(_SoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
		{
			MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		return true;
	}
}