#include "MnTilePalatte.h"
#include "MnResources.h"
#include "MnInput.h"
#include "MnCollider.h"
#include "MnGround.h"
#include <commdlg.h>

namespace Mn
{
	std::unordered_map<UINT64, Tile*> TilePalatte::_Tiles = {};
	Image*	TilePalatte::_Image= nullptr;
	UINT	TilePalatte::_Index = -1;


	void TilePalatte::Initiailize()
	{
		_Image = Resources::Find<Image>(L"TileAtlas");
	}
	void TilePalatte::Update()
	{
	}
	void TilePalatte::Render(HDC hdc)
	{
	}
	void TilePalatte::CreateTile(int index, Vector2 pos)
	{
		Vector2 mousPos = Input::GetMousePos();
		if (mousPos.x >= 920.0f || mousPos.x <= 0.0f)
			return;
		if (mousPos.y >= 720.0f || mousPos.y <= 0.0f)
			return;

		Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		tile->InitializeTile(_Image, index);

		Vector2 tilePos(pos.x * TILE_SIZE_X, pos.y * TILE_SIZE_Y);
		tile->GetComponent<Transform>()->Pos(tilePos);

		if (index <=75 )
		{
			Ground* ground=object::Instantiate<Ground>(eLayerType::Ground);
			ground->GetComponent<Transform>()->Pos(tilePos);
		}

		TileID id;
		id.x = (UINT32)pos.x;
		id.y = (UINT32)pos.y;

		_Tiles.insert(std::make_pair(id.id, tile));
	}
	void TilePalatte::CreateTiles(int index, UINT width, UINT height)
	{
	}
	void TilePalatte::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* file = nullptr;

		_wfopen_s(&file, szFilePath, L"wb");

		if (nullptr == file)
			return;

		std::unordered_map<UINT64, Tile*>::iterator iter = _Tiles.begin();
		for (; iter != _Tiles.end(); iter++)
		{
			int index = iter->second->Index();
			fwrite(&index, sizeof(int), 1, file);

			TileID id;
			id.id = iter->first;
			fwrite(&id.id, sizeof(TileID), 1, file);
		}
		fclose(file);
	}
	void TilePalatte::Load()
	{
	}
	void TilePalatte::Load(const wchar_t* name)
	{
		FILE* file = nullptr;

		const wchar_t* path = L"..\\Resources\\";

		wchar_t pathname[80] = {};
		wcscat_s(pathname, path);
		wcscat_s(pathname, name);

		_wfopen_s(&file, pathname, L"rb");

		if (file == nullptr)
			return;

		while (true)
		{
			int index = -1;
			TileID id;

			if (fread(&index, sizeof(int), 1, file) == NULL)
				break;

			if (fread(&id.id, sizeof(TileID), 1, file) == NULL)
				break;

			CreateTile(index, Vector2(id.x, id.y));
		}

		fclose(file);
	}
	Vector2 TilePalatte::TilePos(Vector2 mousePos)
	{
		int indexY = mousePos.y / TILE_SIZE_Y;
		int indexX = mousePos.x / TILE_SIZE_X;

		return Vector2(indexX, indexY);
	}
}