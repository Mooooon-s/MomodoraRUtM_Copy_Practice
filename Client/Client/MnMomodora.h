#pragma once
#include "MnGameObject.h"
#include "MnTime.h"

namespace Mn {
	class Momodora : public GameObject
	{
	private:

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
