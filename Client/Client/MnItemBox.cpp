#include "MnItemBox.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnInput.h"
namespace Mn
{
	ItemBox::ItemBox()
		:GameObject()
		, _ItemBox(nullptr)
		, _CurrItem(nullptr)
		, _Item()
		,_Idx(0)
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
		
		_Item.name = Item_name::HP;
		_Item._ItemImage = Resources::Load<Image>(L"Itme_Hp", L"..\\Resources\\Item_2.bmp");
		itemBox.push_back(_Item);
		_Item.name = Item_name::Swap;
		_Item._ItemImage = Resources::Load<Image>(L"Itme_Swap", L"..\\Resources\\Item_1.bmp");
		itemBox.push_back(_Item);
		_CurrItem = itemBox[0]._ItemImage;
		GameObject::Initialize();
	}
	void ItemBox::Update()
	{
		if (Input::GetKeyDown(eKeyCode::E))
		{
			_Idx +=1;
			_Idx %= 2;
		}
		_CurrItem = itemBox[_Idx]._ItemImage;
		GameObject::Update();
	}
	void ItemBox::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		TransparentBlt(hdc, pos.x, pos.y, _ItemBox->Width()*3, _ItemBox->Height()*3
			, _ItemBox->Hdc(), 0, 0, _ItemBox->Width(), _ItemBox->Height(), RGB(0, 128, 128));
		TransparentBlt(hdc, pos.x+15, pos.y+15, _CurrItem->Width() * 3, _CurrItem->Height() * 3
			, _CurrItem->Hdc(), 0, 0, _CurrItem->Width(), _CurrItem->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void ItemBox::Release()
	{
		GameObject::Release();
	}
}