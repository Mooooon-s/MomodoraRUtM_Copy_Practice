#pragma once
#include "MnEngine.h"

namespace Mn
{
	class GameObject;
	class Camera
	{
	private:
		enum class CameraState{
			None,
			FadeIN,
			FadeOUT,
			Shake,
		};
		static GameObject*	_Target;
		static Vector2		_Resolution;
		static Vector2		_LookPosition;
		static Vector2		_Distance;

		static CameraState	_Type;
		static class Image* _Cutton;
		static float		_CuttonAlpha;
		static float		_AlphaTime;
		static float		_EndTime;
	public:
		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);
		static void CamMove();
		static void Clear();

		static void SetTarget(GameObject* target) { _Target = target; }
		static GameObject* GetTarget() { return _Target; }
		static Vector2 ComputePos(Vector2 pos) { return pos - _Distance; }


	};
}

