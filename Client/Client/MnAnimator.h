#pragma once
#include "MnComponent.h"
#include "MnAnimation.h"
#include "MnImage.h"

namespace Mn
{
	class Animator : public Component
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
			Event _StartEvent;
			Event _CompleteEvent;
			Event _EndEvent;
			Event _FrameEvent;
		};

	private:
		std::map<std::wstring, Animation*>	_Animations;
		std::map<std::wstring, Events*>		_Events;
		Animation*							_ActiveAnimation;
		bool								_bLoop;

	public:
		Animator();
		~Animator();
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
	public:
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn, UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);
		Animation* GetActiveAnim() { return _ActiveAnimation; }
	public:
		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		std::function<void()>& GetFrameEvent(const std::wstring& name, int frame);
	public:
		void animationAlpha(int alpha) { _ActiveAnimation->Alpha(alpha); }
	};
}

