#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Kaho;
	class Image;
	class Ground;
	class VeiwPoint : public GameObject
	{
	private:
		Kaho*	_Kaho;
		Image*	_Image;
		Ground* _Ground;
		Vector2 _Pos;
		Vector2 _PlayerPos;
	public:
		VeiwPoint();
		~VeiwPoint();
	public:
		void Initialize() override;
		void Update() override;
		void Release() override;
	};
}

