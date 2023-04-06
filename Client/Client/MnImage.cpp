#include "MnImage.h"
#include "Application.h"
#include "MnResources.h"

extern Mn::Application application;

namespace Mn
{
	Image* Image::Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb)
	{
		if (widht == 0 || height == 0)
			return nullptr;

		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC mainHdc = application.GetHdc();

		image->_bitmap = CreateCompatibleBitmap(mainHdc, widht, height);

		image->_hdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->_hdc, image->_bitmap);
		DeleteObject(oldBitmap);

		image->_Width = widht;
		image->_Height = height;

		image->Key(name);
		Resources::Insert<Image>(name, image);

		// Setting Image Color
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->Hdc(), brush);
		Rectangle(image->Hdc(), -1, -1, image->_Width + 1, image->_Height + 1);
		SelectObject(image->Hdc(), oldBrush);
		DeleteObject(oldBrush);

		return image;
	}
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

	COLORREF Image::GetPixel(int x, int y)
	{
		return ::GetPixel(_hdc, x, y);
	}

	void Image::SetPixel(int x, int y, COLORREF color)
	{
		::SetPixel(_hdc, x, y, color);
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