#pragma once
#include "MnEntity.h"

//추상 클래스
namespace Mn {
	class Resource
	{
	private:
		std::wstring _Key;
		std::wstring _path;
		
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		std::wstring Key(void) { return _Key; }
		std::wstring Path(void) { return _path; }
		void Key(const std::wstring& Key) { _Key = Key; }
		void Path(const std::wstring& path) { _path = path; }
	};
}

