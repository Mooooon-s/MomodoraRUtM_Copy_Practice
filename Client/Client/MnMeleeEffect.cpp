#include "MnMeleeEffect.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnCollider.h"
#include "MnObject.h"
#include "MnPlayScene.h"
#include "MnKaho.h"

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
		//-------------------------------------------------------------------------------------------------------------------
		//
		//											Kaho Human Effect Animation
		// 
		//-------------------------------------------------------------------------------------------------------------------
		//7,7,9
		//96*48
		Image* image = Resources::Load<Image>(L"Kaho_Human_Melee_Effect",L"..\\Resources\\Kaho_Effect.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_1_Right", image, Vector2::Zero, 9, 6, 7, Vector2(70,0), 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_1_Left", image, Vector2(0,48), 9, 6, 7, Vector2(-70,0), 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_2_Right", image, Vector2(0,48*2), 9, 6, 7, Vector2(65,0), 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_2_Left", image, Vector2(0, 48*3), 9, 6, 7, Vector2(-65,0), 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_3_Right", image, Vector2(0, 48 * 4), 9, 6, 9, Vector2(65,-15), 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Melee_Attack_3_Left", image, Vector2(0, 48*5), 9, 6, 9, Vector2(-70,-15), 0.06);
		//6,6
		//96*56
		image = Resources::Load<Image>(L"Kaho_Human_Air_Melee_Effect", L"..\\Resources\\Kaho_Effect_air.bmp");
		_Animator->CreateAnimation(L"Kaho_Human_Air_Melee_Attack_1_Right", image, Vector2::Zero, 6, 2, 6, Vector2(70,10), 0.06);
		_Animator->CreateAnimation(L"Kaho_Human_Air_Melee_Attack_1_Left", image, Vector2(0, 56), 6, 2, 6, Vector2(-70,10), 0.06);

		//-------------------------------------------------------------------------------------------------------------------
		//
		//											Kaho Cat Effect Animation
		// 
		//-------------------------------------------------------------------------------------------------------------------
		image = Resources::Load<Image>(L"Kaho_Cat_Melee_Effect_!", L"..\\Resources\\Cat_attack_128_80.bmp");
		_Animator->CreateAnimation(L"Kaho_Cat_Melee_Attack_1_Right", image, Vector2::Zero, 7, 2, 7, Vector2(0,5), 0.06);
		_Animator->CreateAnimation(L"Kaho_Cat_Melee_Attack_1_Left", image, Vector2(0,80), 7, 2, 7, Vector2(0,5), 0.06);

		image = Resources::Load<Image>(L"Kaho_Cat_Melee_Effect_2", L"..\\Resources\\Cat_attack2_128_96.bmp");
		_Animator->CreateAnimation(L"Kaho_Cat_Melee_Attack_2_Right", image, Vector2::Zero, 7, 2, 7, Vector2(5,45), 0.06);
		_Animator->CreateAnimation(L"Kaho_Cat_Melee_Attack_2_Left", image, Vector2(0,96), 7, 2, 7, Vector2(0,45), 0.06);
		
		image = Resources::Load<Image>(L"Kaho_Cat_Melee_Effect_3", L"..\\Resources\\Cat_attack3_128_96.bmp");
		_Animator->CreateAnimation(L"Kaho_Cat_Melee_Attack_3_Right", image, Vector2::Zero, 12, 2, 12, Vector2(0,45), 0.06);
		_Animator->CreateAnimation(L"Kaho_Cat_Melee_Attack_3_Left", image, Vector2(0,96), 12, 2, 12, Vector2(0,45), 0.06);
		//-------------------------------------------------------------------------------------------------------------------
		//
		//											Kaho Human Effect Events
		// 
		//-------------------------------------------------------------------------------------------------------------------
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_1_Right") = std::bind(&MeleeEffect::melee1Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_1_Left") = std::bind(&MeleeEffect::melee1Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_2_Right") = std::bind(&MeleeEffect::melee2Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_2_Left") = std::bind(&MeleeEffect::melee2Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_3_Right") = std::bind(&MeleeEffect::melee3Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Melee_Attack_3_Left") = std::bind(&MeleeEffect::melee3Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Air_Melee_Attack_1_Right") = std::bind(&MeleeEffect::airmeleeComplete, this);
		_Animator->GetCompleteEvent(L"Kaho_Human_Air_Melee_Attack_1_Left") = std::bind(&MeleeEffect::airmeleeComplete, this);

		_Animator->FindAnimation(L"Kaho_Human_Melee_Attack_1_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Human_Melee_Attack_1_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Human_Melee_Attack_2_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Human_Melee_Attack_2_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Human_Melee_Attack_3_Right")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Human_Melee_Attack_3_Left")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);

		_Animator->FindAnimation(L"Kaho_Human_Air_Melee_Attack_1_Right")->GetSprite(2)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Human_Air_Melee_Attack_1_Left")->GetSprite(2)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoHumanMeleeCollider, this);
		//-------------------------------------------------------------------------------------------------------------------
		//
		//											Kaho Cat Effect Events
		// 
		//-------------------------------------------------------------------------------------------------------------------
		_Animator->GetCompleteEvent(L"Kaho_Cat_Melee_Attack_1_Right") = std::bind(&MeleeEffect::melee1Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Cat_Melee_Attack_1_Left") = std::bind(&MeleeEffect::melee1Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Cat_Melee_Attack_2_Right") = std::bind(&MeleeEffect::melee2Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Cat_Melee_Attack_2_Left") = std::bind(&MeleeEffect::melee2Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Cat_Melee_Attack_3_Right") = std::bind(&MeleeEffect::melee3Complete, this);
		_Animator->GetCompleteEvent(L"Kaho_Cat_Melee_Attack_3_Left") = std::bind(&MeleeEffect::melee3Complete, this);

		_Animator->FindAnimation(L"Kaho_Cat_Melee_Attack_1_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoCatMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Cat_Melee_Attack_1_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoCatMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Cat_Melee_Attack_2_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoCatMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Cat_Melee_Attack_2_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoCatMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Cat_Melee_Attack_3_Right")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoCatMeleeCollider, this);
		_Animator->FindAnimation(L"Kaho_Cat_Melee_Attack_3_Left")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&MeleeEffect::kahoCatMeleeCollider, this);
		
		_kaho = PlayScene::GetKaho();
	}
	void MeleeEffect::Update()
	{
		animation();
		effectpos();
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
	void MeleeEffect::effectpos()
	{
		Transform* ktr = _kaho->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		tr->Pos(ktr->Pos());
	}
	void MeleeEffect::animation()
	{
		if (_IsPlaying == false && _kaho->IsCat()==false)
		{
			switch (_Attack)
			{
				//combo1
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
				//combo2
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
				//combo3
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
				break;
				//air
			case 4:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Human_Air_Melee_Attack_1_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Human_Air_Melee_Attack_1_Left", false);
					_IsPlaying = true;
				}
				break;
			default:
				break;
			}

		}
		else if (_IsPlaying == false && _kaho->IsCat() == true)
		{
			switch (_Attack)
			{
				//combo1
			case 1:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_1_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_1_Left", false);
					_IsPlaying = true;
				}
				break;
				//combo2
			case 2:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_2_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_2_Left", false);
					_IsPlaying = true;
				}
				break;
				//combo3
			case 3:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_3_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_3_Left", false);
					_IsPlaying = true;
				}
				break;
				//air
			case 4:
				if (_Dir == eDir::R)
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_1_Right", false);
					_IsPlaying = true;
				}
				else
				{
					_Animator->Play(L"Kaho_Cat_Melee_Attack_1_Left", false);
					_IsPlaying = true;
				}
				break;
			default:
				break;
			}
		}

	}
	void MeleeEffect::kahoHumanMeleeCollider()
	{
		_Collider = AddComponent<Collider>();
		switch (_Attack)
		{
		case 1:
			if(_Dir==eDir::R)
				_Collider->Center(Vector2(35,-110));
			else
				_Collider->Center(Vector2(-140, -110));
			_Collider->Size(Vector2(35*3, 32*3));
			break;
		case 2:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(35, -110));
			else
				_Collider->Center(Vector2(-140, -110));
			_Collider->Size(Vector2(35*3, 32*3));
			break;
		case 3:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(35, -130));
			else
				_Collider->Center(Vector2(-155, -130));
			_Collider->Size(Vector2(40*3, 40*3));
			break;
		case 4:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(-30, -120));
			else
				_Collider->Center(Vector2(-155, -120));
			_Collider->Size(Vector2(40*3, 40*3));
			break;
		default:
			break;
		}
	}
	void MeleeEffect::kahoCatMeleeCollider()
	{
		_Collider = AddComponent<Collider>();
		switch (_Attack)
		{
		case 1:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(30, -110));
			else
				_Collider->Center(Vector2(-135, -110));
			_Collider->Size(Vector2(35*3, 35*3));
			break;
		case 2:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(30, -120));
			else
				_Collider->Center(Vector2(-135, -120));
			_Collider->Size(Vector2(35*3, 40*3));
			break;
		case 3:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(30, -150));
			else
				_Collider->Center(Vector2(-148, -150));
			_Collider->Size(Vector2(40*3, 50*3));
			break;
		case 4:
			if (_Dir == eDir::R)
				_Collider->Center(Vector2(-30, -120));
			else
				_Collider->Center(Vector2(-70, -120));
			_Collider->Size(Vector2(40*3, 40*3));
			break;
		default:
			break;
		}
	}
}