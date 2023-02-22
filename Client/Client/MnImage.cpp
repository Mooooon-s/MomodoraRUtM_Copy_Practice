#include "MnImage.h"
#include "Application.h"

extern Mn::Application application;

namespace Mn
{
	Image::Image()
		: _bitmap(NULL)
		, _hdc(NULL)
		, _Width(0)
		, _Height(0)
	{

	}
	Image::~Image()
	{
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		//이미지 받아오기
		_bitmap = (HBITMAP)LoadImageW(nullptr
			,path.c_str(), IMAGE_BITMAP
			,0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (_bitmap == nullptr)
			return E_FAIL;

		BITMAP bitInfo = {};
		GetObject(_bitmap, sizeof(BITMAP), &bitInfo);

		_Width = bitInfo.bmWidth;
		_Height = bitInfo.bmHeight;

		HDC MainHdc = application.GetHdc();
		_hdc = CreateCompatibleDC(MainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(_hdc, _bitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}

}