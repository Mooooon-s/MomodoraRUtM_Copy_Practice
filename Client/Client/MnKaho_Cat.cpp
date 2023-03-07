#include "MnKaho_Cat.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"

namespace Mn
{
	Kaho_Cat::Kaho_Cat()
		:_Animator(nullptr)
	{
	}
	Kaho_Cat::~Kaho_Cat()
	{
	}
	void Kaho_Cat::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(600.0f,400.0f));
		
		_Animator = AddComponent<Animator>();
		Image* _Image = Resources::Load<Image>(L"Kaho_Cat", L"..\\Resources\\Kaho_Cat.bmp");
		_Animator->CreateAnimation(L"Cat_Attack_1_Right", _Image, Vector2(0, 0), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_1_Left", _Image, Vector2(0, 80), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_2_Right", _Image, Vector2(0, 80 * 2), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_2_Left", _Image, Vector2(0, 80 * 3), 12, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_3_Right", _Image, Vector2(0, 80 * 4), 12, 6, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Attack_3_Left", _Image, Vector2(0, 80 * 5), 12, 6, 12, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat2", L"..\\Resources\\Kaho_Cat_Move.bmp");
		_Animator->CreateAnimation(L"Cat_Idle_Right", _Image, Vector2(0, 0), 12, 8, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Idle_Left", _Image, Vector2(0, 32), 12, 8, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Hurt_Right", _Image, Vector2(32 * 12, 0), 12, 8, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Hurt_Left", _Image, Vector2(32 * 12, 32), 12, 8, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Death_Right", _Image, Vector2(0, 32 * 2), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Death_Left", _Image, Vector2(0, 32 * 3), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Crouch_Right", _Image, Vector2(0, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Crouch_Right", _Image, Vector2(0, 32 * 5), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Idle_Right", _Image, Vector2(32 * 4, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Idle_Right", _Image, Vector2(32 * 4, 32 * 4), 12, 8, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Right", _Image, Vector2(0, 32 * 6), 12, 8, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Crouch_Right", _Image, Vector2(0, 32 * 7), 12, 8, 9, Vector2::Zero, 0.08);

		_Image = Resources::Load<Image>(L"Kaho_Cat3", L"..\\Resources\\Kaho_Cat_Move2.bmp");
		_Animator->CreateAnimation(L"Cat_Jump_Right", _Image, Vector2(0, 0), 11, 9, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Jump_Left", _Image, Vector2(32, 0), 11, 9, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Run_Right", _Image, Vector2(32 * 2, 0), 11, 9, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_to_Run_Left", _Image, Vector2(32 * 4, 0), 11, 9, 2, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Fall_Right", _Image, Vector2(0, 32), 11, 9, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Fall_Left", _Image, Vector2(32 * 3, 32), 11, 9, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Land_Right", _Image, Vector2(0, 32 * 2), 11, 9, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Land_Left", _Image, Vector2(32 * 4, 32 * 2), 11, 9, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Roll_Right", _Image, Vector2(0, 32 * 3), 11, 9, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Roll_Left", _Image, Vector2(0, 32 * 4), 11, 9, 8, Vector2::Zero, 0.08);

		_Animator->Play(L"Cat_Idle_Right", true);
		
	}
	void Kaho_Cat::Update()
	{
		GameObject::Update();
	}
	void Kaho_Cat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Kaho_Cat::Release()
	{
	}
}