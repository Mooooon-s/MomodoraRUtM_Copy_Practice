#pragma once
#include "MnEntity.h"

namespace Mn
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				_Event = std::move(func);
			}
			void operator()()
			{
				if (_Event)
					_Event();
			}
			std::function<void()> _Event;
		};

		struct Events
		{
			Event _FrameEvent;
		};

		struct Sprite
		{
			Vector2 leftTop;
			Vector2 offset;
			Vector2	size;
			float	duration;
			Events	_Events;

			Sprite()
				: leftTop(Vector2::Zero)
				, offset(Vector2::Zero)
				, size(Vector2::Zero)
				, duration(0.0f)
			{
			}
		};

	private:
		std::vector<Sprite> _SpriteSheet;
		Animator*			_Animator;
		Image*				_ImageSheet;
		float				_Time;
		bool				_bComplete;
		int					_SpriteIndex;
		int					_Alpha;
	public:
		Animation();
		~Animation();
	public:
		void Initialize();
		void Update();
		void Render(HDC hdc);
		void Create(Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration);
		void Reset();
		Sprite& GetSprite(int idx) { return _SpriteSheet[idx]; }

	public:
		bool IsComplete() { return _bComplete; }
		void SetAnimator(Animator* animator) { _Animator = animator; }
		void Alpha(int alpha) { _Alpha = alpha; }
	};
}

