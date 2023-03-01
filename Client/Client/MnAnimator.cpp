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
		_ActiveAnimation = FindAnimation(name);
		_bLoop = loop;
		if(!_bLoop)
			_ActiveAnimation->Reset();
	}
}