#pragma once
#include "MnEngine.h"

namespace Mn
{
	class GameObject;
	class Camera
	{
	private:
		static Vector2 _Resolution;
		static Vector2 _LookPosition;
		static Vector2 _Distance;
		static GameObject* _Target;
	public:
		static void Initiailize();
		static void Update();
		static void CamMove();

		static void SetTarget(GameObject* target) { _Target = target; }
		static Vector2 ComputePos(Vector2 pos) { return pos - _Distance; }


	};
}

