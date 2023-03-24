#pragma once
#include "MnTile.h"
#include "MnImage.h"
#include "MnObject.h"

namespace Mn
{
	class TilePalatte
	{
	private:
		static std::unordered_map<UINT64, Tile*>_Tiles;
		static Image*	_Image;
		static UINT		_Index;
	public:
		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);

		static void CreateTile(int index, Vector2 pos);
		static void CreateTiles(int index, UINT width, UINT height);
		static void Save();
		static void Load();

		static Vector2 TilePos(Vector2 mousePos);
		static void Index(UINT index) { _Index = index; }
		static UINT Index() { return _Index; }
	};
}
