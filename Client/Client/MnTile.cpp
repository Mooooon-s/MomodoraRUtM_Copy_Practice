#include "MnTile.h"
#include "MnTransform.h"
#include "MnCamera.h"
#include "MnResources.h"

Mn::Tile::Tile()
	: _Atlas(nullptr)
	, _Index(-1)
	, _X(-1)
	,_Y(-1)
{
}

Mn::Tile::Tile(Vector2 pos)
	: _Atlas(nullptr)
	, _Index(-1)
	, _X(-1)
	, _Y(-1)
{
	GetComponent<Transform>()->Pos(pos);
}

Mn::Tile::~Tile()
{
}

void Mn::Tile::InitializeTile(Image* atlas,int index)
{
	_Index = index;
	if (atlas == nullptr || index < 0)
		return;
	_Atlas = atlas;
	SetIndex(index);
}

void Mn::Tile::SetIndex(int index)
{
	int maxCol = (_Atlas->Width()*3) / (TILE_SIZE_X);
	int maxRow = (_Atlas->Height()*3) / (TILE_SIZE_Y);

	_Y = index / maxCol;
	_X = index % maxCol;

}

void Mn::Tile::Update()
{
}

void Mn::Tile::Render(HDC hdc)
{
	if (_Atlas == nullptr || _Index < 0)
		return;

	Transform* tr = GetComponent<Transform>();

	Vector2 renderPos = Camera::ComputePos(tr->Pos());

	TransparentBlt(hdc
		, renderPos.x, renderPos.y
		, TILE_SIZE_X, TILE_SIZE_Y
		, _Atlas->Hdc()
		, TILE_SIZE_X /3* _X, TILE_SIZE_Y /3* _Y
		, TILE_SIZE_X/3, TILE_SIZE_X/3
		, RGB(0, 128, 128));
}
