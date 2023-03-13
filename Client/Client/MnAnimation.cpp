#include "MnAnimation.h"
#include "MnImage.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnGameObject.h"
#include "MnTime.h"
#include "MnCamera.h"

namespace Mn
{
	Animation::Animation()
		:_ImageSheet(nullptr)
		,_Animator(nullptr)
		,_SpriteIndex(0)
		,_Time(0)
		,_bComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Initialize()
	{
	}
	void Animation::Update()
	{
		if (_bComplete)
			return;

		_Time += Time::DeltaTime();
		if (_SpriteSheet[_SpriteIndex].duration < _Time)
		{
			_Time = 0.0f;
			if(_SpriteSheet.size() <= _SpriteIndex+1)
				_bComplete = true;
			else
				_SpriteIndex++;
		}
	}
	void Animation::Render(HDC hdc)
	{
		Transform* tr = _Animator->Owner()->GetComponent<Transform>();
		Vector2 scale = tr->Scale();

		Vector2 pos = tr->Pos();
		if (Camera::GetTarget() != nullptr)
			pos = Camera::ComputePos(pos);
		pos += _SpriteSheet[_SpriteIndex].offset;
		pos.x -= ((_SpriteSheet[_SpriteIndex].size.x / 2.0f)*scale.x);
		pos.y -= ((_SpriteSheet[_SpriteIndex].size.y)*scale.y);
		
		GdiTransparentBlt(hdc, pos.x, pos.y
			, _SpriteSheet[_SpriteIndex].size.x*scale.x
			, _SpriteSheet[_SpriteIndex].size.y*scale.y
			, _ImageSheet->Hdc()
			, _SpriteSheet[_SpriteIndex].leftTop.x, _SpriteSheet[_SpriteIndex].leftTop.y
			, _SpriteSheet[_SpriteIndex].size.x, _SpriteSheet[_SpriteIndex].size.y,
			RGB(0, 128, 128));
	}
	void Animation::Create(Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration)
	{
		_ImageSheet = sheet;
		Vector2 size = Vector2::One;
		size.x = _ImageSheet->Width() / (float)coulmn;
		size.y = _ImageSheet->Height() / (float)row;

		for (int i = 0; i < spriteLength; i++)
		{
			Sprite spriteInfo;

			spriteInfo.leftTop.x = leftTop.x+(size.x*i);
			spriteInfo.leftTop.y = leftTop.y;
			spriteInfo.size = size;
			spriteInfo.offset = offset;
			spriteInfo.duration = duration;

			_SpriteSheet.push_back(spriteInfo);
		}

	}
	void Animation::Reset()
	{
		_SpriteIndex = 0;
		_Time = 0.0f;
		_bComplete = false;
	}
}