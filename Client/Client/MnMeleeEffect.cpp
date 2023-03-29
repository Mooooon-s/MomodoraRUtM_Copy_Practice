#include "MnMeleeEffect.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnCollider.h"
#include "MnObject.h"

namespace Mn
{
	MeleeEffect::MeleeEffect()
		: _Animator(nullptr)
		,_Dir(eDir::R)
		,_Attack(0)
		,_IsEnd(false)
		,_IsPlaying(false)
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
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_1_Right", image, Vector2::Zero, 9, 6, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_1_Left", image, Vector2(0,48), 9, 6, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_2_Right", image, Vector2(0,48*2), 9, 6, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_2_Left", image, Vector2(0, 48*3), 9, 6, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_3_Right", image, Vector2(0,48*4), 9, 6, 7, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_3_Left", image, Vector2(0, 48*5), 9, 6, 7, Vector2::Zero, 0.06);
		//6,6
		//96*56
		image = Resources::Load<Image>(L"Kaho_Human_Air_Melee_Effect", L"..\\Resources\\Kaho_Effect_air.bmp");
		_Animator->CreateAnimation(L"Kaho_Human_Air_Melee_Attack_1_Right", image, Vector2::Zero, 2, 6, 6, Vector2::Zero, 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Air_Melee_Attack_1_Left", image, Vector2(0, 56), 2, 6, 6, Vector2::Zero, 0.06);

		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_1_Right") = std::bind(&MeleeEffect::melee1Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_1_Left") = std::bind(&MeleeEffect::melee1Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_2_Right") = std::bind(&MeleeEffect::melee2Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_2_Left") = std::bind(&MeleeEffect::melee2Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_3_Right") = std::bind(&MeleeEffect::melee3Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_3_Left") = std::bind(&MeleeEffect::melee3Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Air_Melee_Attack_1_Right") = std::bind(&MeleeEffect::airmeleeComplete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Air_Melee_Attack_1_Left") = std::bind(&MeleeEffect::airmeleeComplete, this);
	}
	void MeleeEffect::Update()
	{
		if (_IsPlaying == false)
		{
			switch (_Attack)
			{
			case 1:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Human_Melee_Attack_1_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Human_Melee_Attack_1_Left", false);
					_IsPlaying = true;
				}
				break;
			case 2:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Human_Melee_Attack_2_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Human_Melee_Attack_2_Left", false);
					_IsPlaying = true;
				}
				break;
			case 3:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Human_Melee_Attack_3_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Human_Melee_Attack_3_Left", false);
					_IsPlaying = true;
				}
			case 4:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Human_Air_Melee_Attack_1_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Human_Air_Melee_Attack_1_Right", false);
					_IsPlaying = true;
				}
				break;
			default:
				break;
			}

		}
		if (_IsEnd)
		{
			object::Destory(this);
		}
		GameObject::Update();
	}
	void MeleeEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
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
	void MeleeEffect::melee1Complete()
	{
		_IsEnd = true;
	}
	void MeleeEffect::melee2Complete()
	{
		_IsEnd = true;
	}
	void MeleeEffect::melee3Complete()
	{
		_IsEnd = true;
	}
	void MeleeEffect::airmeleeComplete()
	{
		_IsEnd = true;
	}
}