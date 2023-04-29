#pragma once
#include "Commoninclude.h"

namespace Mn
{
	class SoundManager
	{
	private:
		static LPDIRECTSOUND8 _SoundDevice;
	public:
		static bool Initialize();
		static LPDIRECTSOUND8 GetDevice() { return _SoundDevice; }
	};
}

