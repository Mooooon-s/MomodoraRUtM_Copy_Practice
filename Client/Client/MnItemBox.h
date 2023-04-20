#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class ItemBox : public GameObject
	{
	private:
		enum class Item_name
		{
			HP,
			Swap,
		};
		struct item
		{
			Item_name name;
			Image* _ItemImage;
		};
		item _Item;
		std::vector<item> itemBox;
		Image* _ItemBox;
		Image* _CurrItem;
		int		_Idx;
	public:
		ItemBox();
		~ItemBox();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		int GetItemNum() { return (int)itemBox[_Idx].name; }
		void IdxNum(int num) { _Idx = num; }
	};
}

