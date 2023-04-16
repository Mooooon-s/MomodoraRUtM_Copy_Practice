#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class HitEffect : public GameObject
	{
	private:
		Animator*	_Animator;
		Image*		_Image;
		bool		_IsEnd;
	public:
		HitEffect();
		~HitEffect();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	private:
		void Destroy();
	};
}

