#include "MnToolScene.h"
#include "MnImage.h"
#include "MnResources.h"
#include "Application.h"
#include "MnTilePalatte.h"
#include "MnInput.h"
#include "MnCamera.h"

extern Mn::Application application;

namespace Mn
{
	HDC ToolScene::_Tilehdc = nullptr;
	HBITMAP ToolScene::_TileBitmap = nullptr;

	ToolScene::ToolScene()
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		Scene::Initialize();
		TilePalatte::Initiailize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
		Vector2  temp = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 pos = Input::GetMousePos();
			pos -= Camera::ComputePos(Vector2::Zero);
			pos = TilePalatte::TilePos(pos);

			UINT tileIndxe = TilePalatte::Index();
			TilePalatte::CreateTile(tileIndxe, pos);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			TilePalatte::Save();
		}
		if (Input::GetKeyDown(eKeyCode::L))
		{

		}
	}

	void ToolScene::Render(HDC hdc)
	{
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

		Vector2 startPos(0, 0);
		startPos = Camera::ComputePos(startPos);

		int maxRow = application.Height() / TILE_SIZE_Y + 1;
		for (size_t y = 0; y < maxRow*3; y++)
		{
			MoveToEx(hdc, startPos.x, TILE_SIZE_Y * y+ startPos.y, NULL);
			LineTo(hdc, application.Width(), TILE_SIZE_Y * y+ startPos.y);
		}
		int maxColumn = application.Width() / TILE_SIZE_X + 1;
		for (size_t x = 0; x < maxColumn*3; x++)
		{
			MoveToEx(hdc, TILE_SIZE_X * x+ startPos.x, startPos.y, NULL);
			LineTo(hdc, TILE_SIZE_X * x+ startPos.x, application.Height());
		}
		(HPEN)SelectObject(hdc, oldPen);
		DeleteObject(redPen);

		Scene::Render(hdc);
	}

	void ToolScene::Release()
	{
		Scene::Release();
	}

	void ToolScene::OnEnter()
	{
	}

	void ToolScene::OnExit()
	{
	}

}
	#include "Resource.h"
	LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CREATE:
		{
			Mn::Image* tile = Mn::Resources::Load<Mn::Image>(L"TileAtlas", L"..\\Resources\\tile.bmp");

			RECT rect = { 0, 0, tile->Width(), tile->Height() };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

			// 윈도우 크기 변경및 출력 설정
			SetWindowPos(hWnd
				, nullptr, 920, 0
				, (rect.right - rect.left) * 3
				, (rect.bottom - rect.top) * 3
				, 0);
			ShowWindow(hWnd, true);
		}

		case WM_LBUTTONDOWN:
		{

			if (GetFocus())
			{
				::POINT mousePos = {};
				::GetCursorPos(&mousePos);
				::ScreenToClient(application.GetToolHwnd(), &mousePos);

				int x = mousePos.x / TILE_SIZE_X;
				int y = mousePos.y / TILE_SIZE_Y;

				int index = (y * 31) + (x % 31);
				Mn::TilePalatte::Index(index);
			}
		}
		break;
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			Mn::Image* tile = Mn::Resources::Find<Mn::Image>(L"TileAtlas");
			TransparentBlt(hdc, 0, 0, tile->Width()*3, tile->Height()*3, tile->Hdc(), 0, 0, tile->Width(), tile->Height(), SRCCOPY);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}