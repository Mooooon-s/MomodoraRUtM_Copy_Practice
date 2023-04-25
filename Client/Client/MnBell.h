#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class Bell : public GameObject
	{
	private:
		Collider*	_Collider;
		Image*		_Image;
		Image*		_BellUI;
		int			_BellNumber;
		bool		_ON;
	public:
		Bell();
		~Bell();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;
	public:
		void BellNumber(int num) { _BellNumber = num; }
	};
}

