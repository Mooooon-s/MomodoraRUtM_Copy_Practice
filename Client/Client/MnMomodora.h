#pragma once
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnImage.h"

namespace Mn {
	class Momodora : public GameObject
	{
	private:
		Image*	_Image;
		float	_Time;
		int		_Idx;
	public:
		Momodora();
		~Momodora();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	};
}
