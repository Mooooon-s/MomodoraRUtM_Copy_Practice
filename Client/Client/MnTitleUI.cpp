#include "MnTitleUI.h"
#include "MnResources.h"
#include "MnTime.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnTransform.h"
#include "MnCamera.h"

namespace Mn
{
	TitleUI::TitleUI()
		:_Idx(0)
		,_Time(0)
	{
	}
	TitleUI::~TitleUI()
	{
	}
	void TitleUI::Initialize()
	{
		Image* _Image = Resources::Load<Image>(L"TitleName", L"..\\Resources\\Title_Animation.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"Title_Animation", _Image, Vector2::Zero, 5, 2, 5, Vector2((324 - 118), (244 - 82)), 0.1f);
		
		Transform* tr = animator->Owner()->GetComponent<Transform>();
		Vector2 pos = Vector2::Zero;
		tr->Pos(Vector2((324-137)*3,(244-54)*3));
		pos = Camera::ComputePos(tr->Pos());
		animator->Play(L"Title_Animation", true);

		GameObject::Initialize();
	}
	void TitleUI::Update()
	{
		GameObject::Update();
	}
	void TitleUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void TitleUI::Release()
	{
		GameObject::Release();
	}
}