#include "MnTilePalatte.h"
#include "MnResources.h"
#include "MnInput.h"

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
		Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		tile->InitializeTile(_Image, index);

		Vector2 tilePos(pos.x * TILE_SIZE_X, pos.y * TILE_SIZE_Y);
		tile->GetComponent<Transform>()->Pos(tilePos);
	}
	void TilePalatte::CreateTiles(int index, UINT width, UINT height)
	{
	}
	void TilePalatte::Save()
	{
	}
	void TilePalatte::Load()
	{
	}
	Vector2 TilePalatte::TilePos(Vector2 mousePos)
	{
		int indexY = mousePos.y / TILE_SIZE_Y*3;
		int indexX = mousePos.x / TILE_SIZE_X*3;

		return Vector2();
	}
}