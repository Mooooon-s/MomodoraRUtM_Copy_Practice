#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class ItemBox : public GameObject
	{
	private:
		Image* _ItemBox;
		Image* _Item;
	public:
		ItemBox();
		~ItemBox();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	};
}

