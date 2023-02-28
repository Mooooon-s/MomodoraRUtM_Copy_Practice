#pragma once
#include "MnComponent.h"
#include "MnAnimation.h"
#include "MnImage.h"

namespace Mn
{
	class Animator : public Component
	{
	private:
		std::map<std::wstring, Animation*> _Animations;
		Animation* _ActiveAnimation;
		bool _bLoop;
	public:
		Animator();
		~Animator();

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

		
	};
}

