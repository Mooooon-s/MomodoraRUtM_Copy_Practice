#include "MnMeleeEffect.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnCollider.h"

namespace Mn
{
	MeleeEffect::MeleeEffect()
	{
	}
	MeleeEffect::~MeleeEffect()
	{
	}
	void MeleeEffect::Initialize()
	{
		//7,7,9
		//96*48
		Image* image = Resources::Load<Image>(L"Kaho_Human_Melee_Effect",L"..\\Resources\\Kaho_Effect.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_1_Right", image, Vector2::Zero, 6, 9, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_1_Left", image, Vector2(0,48), 6, 9, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_2_Right", image, Vector2(0,48*2), 6, 9, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_2_Left", image, Vector2(0, 48*3), 6, 9, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_3_Right", image, Vector2(0,48*4), 6, 9, 9, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_3_Left", image, Vector2(0, 48*5), 6, 9, 9, Vector2::Zero, 0.06);
		//6,6
		//96*56
		image = Resources::Load<Image>(L"Kaho_Human_Air_Melee_Effect", L"..\\Resources\\Kaho_Effect_air.bmp");
		_Animator->CreateAnimation(L"Kaho_Human_Air_Melee_Attack_1_Right", image, Vector2::Zero, 2, 6, 6, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Air_Melee_Attack_1_Left", image, Vector2(0, 56), 2, 6, 6, Vector2::Zero, 0.06);


		GameObject::Initialize();
	}
	void MeleeEffect::Update()
	{
	}
	void MeleeEffect::Render(HDC hdc)
	{
	}
	void MeleeEffect::Release()
	{
	}
	void MeleeEffect::OnCollisionEnter(Collider* other)
	{
	}
	void MeleeEffect::OnCollisionStay(Collider* other)
	{
	}
	void MeleeEffect::OnCollisionExit(Collider* other)
	{
	}
}