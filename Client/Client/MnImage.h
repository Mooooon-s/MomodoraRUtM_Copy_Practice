#pragma once
#include "MnResource.h"

namespace Mn
{
	class Image : public Resource
	{
	private:

		HBITMAP _bitmap;
		HDC		_hdc;
		UINT	_Width;
		UINT	_Height;
	public:
		Image();
		~Image();

		static Image* Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb = RGB(255, 255, 255));
		UINT Width(void)  { return _Width; }
		UINT Height(void) { return _Height; }
		HDC  Hdc(void)    { return _hdc; }
		HBITMAP Bitmap(void) { return _bitmap; }

		virtual HRESULT Load(const std::wstring& path) override;
	};
}
