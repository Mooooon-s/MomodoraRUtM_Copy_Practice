#include "MnArrow.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnObject.h"
namespace Mn
{
	Arrow::Arrow()
		:_Animator(nullptr)
	{
		Initialize();
	}
	Arrow::~Arrow()
	{
	}
	void Arrow::Initialize()
	{
		Image* image = Resources::Load<Image>(L"Arrow", L"..\\Resources\\Arrow.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Arrow_Right", image, Vector2(0, 0), 2, 1, 1, Vector2::Zero, 0.08f);
		_Animator->CreateAnimation(L"Arrow_Left", image, Vector2(32, 0), 2, 1, 1, Vector2::Zero, 0.08f);
	}
	void Arrow::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		pos.x += 1000.0f * Time::DeltaTime();
		tr->Pos(pos);
		_Animator->Play(L"Arrow_Right", false);
	}
	void Arrow::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Arrow::Release()
	{
	}
}