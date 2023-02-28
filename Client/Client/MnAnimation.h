#pragma once
#include "MnEntity.h"

namespace Mn
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 offset;
			Vector2	size;
			float	duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, offset(Vector2::Zero)
				, size(Vector2::Zero)
				, duration(0.0f)
			{
			}
		};
	private:
		Image* _ImageSheet;
		Animator* _Animator;
		std::vector<Sprite> _SpriteSheet;
		int _SpriteIndex;
		float _Time;
		bool _bComplete;
	public:
		Animation();
		~Animation();
	public:
		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Create(Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration);
		void Reset();

	public:
		bool IsComplete() { return _bComplete; }
		void SetAnimator(Animator* animator) { _Animator = animator; }
	};
}

