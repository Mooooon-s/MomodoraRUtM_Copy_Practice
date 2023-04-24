#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Collider;
	class MagArrow : public GameObject
	{
	private:
		Image*		_Arrow;
		Image*		_BlowUpArrow;
		Collider*	_Collider;
		float		_Timer;
		bool		_BlowUp;
	public:
		MagArrow();
		~MagArrow();
	public:
		void Initialize() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
	public:
		void OnCollisionEnter(class Collider* other) override;
	public:
		void BlowUp(bool blow) { _BlowUp = blow; }
	};
}

