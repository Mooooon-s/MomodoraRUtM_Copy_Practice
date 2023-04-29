#pragma once
#include "MnResource.h"

namespace Mn
{
	class Sound : public Resource
	{
	private:
		LPDIRECTSOUNDBUFFER		_SoundBuffer;
		DSBUFFERDESC			_BufferDesc;
		int _Volume;
	public:
		virtual HRESULT Load(const std::wstring& path) override;
		bool LoadWavFile(const std::wstring& path);
		void Play(bool loop);
		void Stop(bool reset);
		void SetPosition(float position, bool loop);
		void SetVolume(float volume);
		int GetDecibel(float volume);
	};
}

