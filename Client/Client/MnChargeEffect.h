#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class ChargeEffect : public GameObject
	{
	private:
		Image*		_Image;
		Animator*	_Animator;
		GameObject* _Owner;
	public:
		ChargeEffect();
		~ChargeEffect();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void GetOwnerObject(GameObject* owner) { _Owner = owner; }
	private:
		void Done();
	};
}

