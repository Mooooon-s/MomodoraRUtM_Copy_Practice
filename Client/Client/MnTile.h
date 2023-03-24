#pragma once
#include "MnImage.h"
#include "MnGameObject.h"

namespace Mn
{
	class Tile : public GameObject
	{
	private:
		Image*	_Atlas;
		int		_Index;
		int		_X;
		int		_Y;
	public:
		Tile();
		Tile(Vector2 pos);
		~Tile();
	public:
		void InitializeTile(Image* atlas, int index);
		void SetIndex(int index);

		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		UINT Y() { return _Y; }
		UINT X() { return _X; }
		UINT Index() { return _Index; }
	};
}

