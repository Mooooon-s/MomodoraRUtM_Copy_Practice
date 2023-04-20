#include "MnItemBox.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnImage.h"
namespace Mn
{
	ItemBox::ItemBox()
		:GameObject()
		, _ItemBox(nullptr)
		, _Item(nullptr)
	{
	}
	ItemBox::~ItemBox()
	{
	}
	void ItemBox::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(10.0f, 50.0f));
		_ItemBox = Resources::Load<Image>(L"ItmeBox", L"..\\Resources\\Item_Box.bmp");
	}
	void ItemBox::Update()
	{
		GameObject::Update();
	}
	void ItemBox::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		TransparentBlt(hdc, pos.x, pos.y, _ItemBox->Width()*3, _ItemBox->Height()*3
			, _ItemBox->Hdc(), 0, 0, _ItemBox->Width(), _ItemBox->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void ItemBox::Release()
	{
		GameObject::Release();
	}
}