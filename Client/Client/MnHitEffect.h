#pragma once
#include "MnGameObject.h"
namespace Mn
{
	class Image;
	class Animator;
	class HitEffect : public GameObject
	{
	private:
		enum class eDir
		{
			R,
			L,
		};
		Animator*	_Animator;
		Image*		_Image;
		eDir		_Dir;
		bool		_IsEnd;
	public:
		HitEffect();
		~HitEffect();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
	public:
		void Dir(int dir);
		void AnimationCntrl(int type);
	private:
		void Destroy();
	};
}

