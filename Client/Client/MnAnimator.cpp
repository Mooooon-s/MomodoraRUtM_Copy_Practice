#include "MnAnimator.h"

namespace Mn
{
	Animator::Animator()
		:Component(eComponentType::Animator)
		,_ActiveAnimation(nullptr)
		,_bLoop(false)
	{
	}
	Animator::~Animator()
	{
		for (auto animation : _Animations)
		{
			delete animation.second;
			animation.second = nullptr;
		}
		for (auto e : _Events)
		{
			delete e.second;
			e.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (_ActiveAnimation)
		{
			_ActiveAnimation->Update();
			if (_bLoop == true && _ActiveAnimation->IsComplete())
			{
				Animator::Events* events
					= FindEvents(_ActiveAnimation->GetName());

				if (events != nullptr)
					events->_CompleteEvent();
				_ActiveAnimation->Reset();
			}
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (_ActiveAnimation)
		{
			_ActiveAnimation->Render(hdc);
		}
	}
	void Animator::Release()
	{
	}
	void Animator::CreateAnimation(const std::wstring& name
		, Image* sheet
		, Vector2 leftTop
		, UINT coulmn, UINT row, UINT spriteLength
		, Vector2 offset, float duration)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(sheet, leftTop, coulmn, row, spriteLength, offset, duration);
		animation->SetName(name);
		animation->SetAnimator(this);

		_Animations.insert(std::make_pair(name, animation));
		Events* event = new Events();
		_Events.insert(std::make_pair(name, event));
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter = _Animations.find(name);
		if(iter== _Animations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::Play(const std::wstring& name, bool loop)
	{
		if (_ActiveAnimation != nullptr)
		{
			Animator::Events* preEvents
				= FindEvents(_ActiveAnimation->GetName());
			if (preEvents != nullptr)
				preEvents->_EndEvent();
		}

		_ActiveAnimation = FindAnimation(name);
		_bLoop = loop;

		if(!_bLoop)
			_ActiveAnimation->Reset();

		Animator::Events* events
			= FindEvents(_ActiveAnimation->GetName());

		if (events != nullptr)
			events->_StartEvent();


	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter = _Events.find(name);
		if (iter == _Events.end())
			return nullptr;
		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events = FindEvents(animation->GetName());

		return events->_StartEvent._Event;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events = FindEvents(animation->GetName());

		return events->_CompleteEvent._Event;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);

		Animator::Events* events = FindEvents(animation->GetName());

		return events->_EndEvent._Event;
	}
}