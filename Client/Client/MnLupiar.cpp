#include "MnLupiar.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnMonMeleeAttack.h"
#include "MnObject.h"
#include "MnLupiarBall.h"
#include "MnKaho.h"
#include "MnSceneManager.h"
#include "MnHitEffect.h"
#include "MnChargeEffect.h"
#include "MnBossHpBar.h"
#include "MnStage3_3.h"
#include "MnSound.h"

namespace Mn
{
	Lupiar::Lupiar()
		: GameObject()
		, _State(eLupiarState::Idle)
		, _Dir(eDir::L)
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Collider(nullptr)
		, _ParringSound(nullptr)
		, _HurtTime(0.0f)
		, _Ready(0.0f)
		, _MoveSpeed(100.0f)
		, _Dash(false)
		, _Count(0)
		, _LupiarBall(nullptr)
		, _MeleeAttack(nullptr)
		, _Kaho(nullptr)
		, _HpBar(nullptr)
		, _KnockBack(0.0f)
		, _Hp(100)
		, _SoundPack()
	{
	}
	Lupiar::~Lupiar()
	{
	}
	void Lupiar::Initialize()
	{
		//48 48
		GameObject::SetName(L"Boss");

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-12.0f * 3, -35.0f * 3));
		_Collider->Size(Vector2(24.0f * 3, 35.0f * 3));

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Image = Resources::Load<Image>(L"Lupiar", L"..\\Resources\\Lupiar_1.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Lupiar_Idle_Left", _Image, Vector2::Zero, 8, 6, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Idle_Right", _Image, Vector2(0,48), 8, 6, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Roll_Left", _Image, Vector2(0,48*2), 8, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Roll_Right", _Image, Vector2(0,48*3), 8, 6, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Hurt_Left", _Image, Vector2(0,48*4), 8, 6, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Hurt_Right", _Image, Vector2(0,48*5), 8, 6, 1, Vector2::Zero, 0.08);
		
		//128 96
		_Image = Resources::Load<Image>(L"Lupiar_Attack_1", L"..\\Resources\\Lupiar_2.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack1_Left", _Image, Vector2::Zero, 9, 2, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack1_Right", _Image, Vector2(0,96), 9, 2, 9, Vector2::Zero, 0.08);
		//80,48
		_Image = Resources::Load<Image>(L"Lupiar_Attack_2", L"..\\Resources\\Lupiar_3.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack2_Left", _Image, Vector2::Zero, 10, 2, 10, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack2_Right", _Image, Vector2(0,48), 10, 2, 10, Vector2::Zero, 0.08);
		//80,48
		_Image = Resources::Load<Image>(L"Lupiar_Attack_3", L"..\\Resources\\Lupiar_4.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack3_Left", _Image, Vector2::Zero, 18, 2, 18, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack3_Right", _Image, Vector2(0, 48), 18, 2, 18, Vector2::Zero, 0.08);
		//92 96
		_Image = Resources::Load<Image>(L"Lupiar_Attack_4", L"..\\Resources\\Lupiar_5.bmp");
		_Animator->CreateAnimation(L"Lupiar_Attack4_Left", _Image, Vector2::Zero, 9, 2, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Lupiar_Attack4_Right", _Image, Vector2(0,96), 9, 2, 9, Vector2::Zero, 0.08);


		_Animator->GetCompleteEvent(L"Lupiar_Roll_Left") = std::bind(&Lupiar::afterAction, this);
		_Animator->GetCompleteEvent(L"Lupiar_Roll_Right") = std::bind(&Lupiar::afterAction, this);

		_Animator->FindAnimation(L"Lupiar_Attack1_Left")->GetSprite(1)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Dash, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Dash, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Right")->GetSprite(1)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Dash, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Dash, this);

		_Animator->FindAnimation(L"Lupiar_Attack1_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Left")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Right")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn1Attack, this);

		_Animator->FindAnimation(L"Lupiar_Attack1_Left")->GetSprite(8)._Events._FrameEvent._Event = std::bind(&Lupiar::afterAction, this);
		_Animator->FindAnimation(L"Lupiar_Attack1_Right")->GetSprite(8)._Events._FrameEvent._Event = std::bind(&Lupiar::afterAction, this);


		_Animator->FindAnimation(L"Lupiar_Attack2_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn2Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack2_Left")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn2Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack2_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn2Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack2_Right")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn2Attack, this);
		
		_Animator->FindAnimation(L"Lupiar_Attack3_Right")->GetSprite(12)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn3Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack3_Left")->GetSprite(12)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn3Attack, this);

		_Animator->FindAnimation(L"Lupiar_Attack4_Right")->GetSprite(2)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn4Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack4_Left")->GetSprite(2)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn4Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack4_Right")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn4Attack, this);
		_Animator->FindAnimation(L"Lupiar_Attack4_Left")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Lupiar::pattarn4Attack, this);


		_Animator->GetCompleteEvent(L"Lupiar_Attack2_Left") = std::bind(&Lupiar::afterAction, this);
		_Animator->GetCompleteEvent(L"Lupiar_Attack2_Right") = std::bind(&Lupiar::afterAction, this);
		_Animator->GetCompleteEvent(L"Lupiar_Attack3_Left") = std::bind(&Lupiar::afterAction, this);
		_Animator->GetCompleteEvent(L"Lupiar_Attack3_Right") = std::bind(&Lupiar::afterAction, this);
		_Animator->GetCompleteEvent(L"Lupiar_Attack4_Right") = std::bind(&Lupiar::afterAction, this);
		_Animator->GetCompleteEvent(L"Lupiar_Attack4_Left") = std::bind(&Lupiar::afterAction, this);

		_Animator->GetStartEvent(L"Lupiar_Roll_Left") = std::bind(&Lupiar::RollSound, this);
		_Animator->GetStartEvent(L"Lupiar_Roll_Right") = std::bind(&Lupiar::RollSound, this);

		_Animator->Play(L"Lupiar_Idle_Right", true);
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> playerObj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerObj)
		{
			if (dynamic_cast<Kaho*>(v))
			{
				_Kaho = dynamic_cast<Kaho*>(v);
				break;
			}
		}
		_HpBar = object::Instantiate<BossHpBar>(Vector2(150, 675),eLayerType::UI);

		_ParringSound = Resources::Load<Sound>(L"Parring", L"..\\Resources\\Sound\\Imp\\Imp_Sheld.wav");
		_SoundPack.push_back(Resources::Load<Sound>(L"Rolling", L"..\\Resources\\Sound\\Kaho_Human\\Roll.wav"));
		_SoundPack.push_back(Resources::Load<Sound>(L"pattarn", L"..\\Resources\\Sound\\Explosion.wav"));

		GameObject::Initialize();
	}
	void Lupiar::Update()
	{
		_HpBar->Hp(_Hp);
		switch (_State)
		{
		case eLupiarState::Idle:
			idle();
			break;
		case eLupiarState::Hurt:
			hurt();
			break;
		case eLupiarState::Death:
			death();
			break;
		case eLupiarState::Roll:
			roll();
			break;
		case eLupiarState::Pattarn1:
			pattarn1();
			break;
		default:
			break;
		}

		if (_HurtTime == 0)
			_KnockBack += Time::DeltaTime();

		if (_Count >= 2 && _KnockBack >= 15.0f)
		{
			_State = eLupiarState::Hurt;
			animationCtrl();
			_KnockBack = 0;
		}

		if (_Hp <= 0 && _State != eLupiarState::Death)
		{
			_State = eLupiarState::Death;
		}

		GameObject::Update();
	}
	void Lupiar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Lupiar::Release()
	{
		GameObject::Release();
	}
	void Lupiar::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			_Hp -= 3;
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			pos.y -= (_Collider->Size().y / 2.0f);
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			if (_Hp <= 0)
			{
				hitEffect->AnimationCntrl(0);
			}
			else
			{
				hitEffect->AnimationCntrl(2);
			}
			if (_KnockBack >= 15.0f)
				_Count++;
		}
		if (other->Owner()->GetName() == L"Arrow")
		{
			_ParringSound->Play(false);
		}
	}
	void Lupiar::OnCollisionStay(Collider* other)
	{
	}
	void Lupiar::OnCollisionExit(Collider* other)
	{
	}
	void Lupiar::think()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		ChargeEffect* effect = object::Instantiate<ChargeEffect>(Vector2(pos.x, pos.y - (24 * 3)), eLayerType::ChargeEffect);
		effect->GetOwnerObject(this);
		int num = (rand() % 5)+3;
		_State = eLupiarState(num);
		animationCtrl();
	}
	void Lupiar::idle()
	{
		_Ready += Time::DeltaTime();
		if(_Ready>=2.0f)
		{
			think();
			_Ready = 0;
		}
	}
	void Lupiar::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime >= 2)
		{
			_HurtTime = 0;
			_Count = 0;
			_State = eLupiarState::Idle;
			animationCtrl();
		}
	}
	void Lupiar::death()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime >= 0.5)
		{
			_HurtTime = 0;
			dynamic_cast<Stage3_3*>(SceneManager::ActiveScene())->Page(true);
			_HpBar->State(eState::Death);
			this->State(eState::Death);
		}
	}
	void Lupiar::roll()
	{
		_MoveSpeed = 300.0f;
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Dir == eDir::R)
			pos.x += _MoveSpeed * Time::DeltaTime();
		else
			pos.x -= _MoveSpeed * Time::DeltaTime();
		Tr->Pos(pos);
	}
	void Lupiar::pattarn1()
	{
		if (_Dash == true)
		{
			_MoveSpeed = 50.0f;
			Transform* Tr = GetComponent<Transform>();
			Vector2 pos = Tr->Pos();
			if (_Dir == eDir::R)
				pos.x += _MoveSpeed * Time::DeltaTime();
			else
				pos.x -= _MoveSpeed * Time::DeltaTime();
			Tr->Pos(pos);
		}
	}
	void Lupiar::animationCtrl()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		float distX = Tr->Pos().x - playerTr->Pos().x;
		float distY = Tr->Pos().y - playerTr->Pos().y;
		Vector2 pos = Tr->Pos();
		if (distX <= 0)
		{
			_Dir = eDir::R;
		}
		if (distX > 0)
		{
			_Dir = eDir::L;
		}

		switch (_State)
		{
		case eLupiarState::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Idle_Right", true);
			else
				_Animator->Play(L"Lupiar_Idle_Left", true);
			break;
		case eLupiarState::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Hurt_Right", true);
			else
				_Animator->Play(L"Lupiar_Hurt_Left", true);
			break;
		case eLupiarState::Death:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Hurt_Right", true);
			else
				_Animator->Play(L"Lupiar_Hurt_Left", true);
			break;
		case eLupiarState::Roll:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Roll_Right", false);
			else
				_Animator->Play(L"Lupiar_Roll_Left", false);
			break;
		case eLupiarState::Pattarn1:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Attack1_Right", false);
			else
				_Animator->Play(L"Lupiar_Attack1_Left", false);
			break;
		case eLupiarState::Pattarn2:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Attack2_Right", false);
			else
				_Animator->Play(L"Lupiar_Attack2_Left", false);
			break;
		case eLupiarState::Pattarn3:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Attack3_Right", false);
			else
				_Animator->Play(L"Lupiar_Attack3_Left", false);
			break;
		case eLupiarState::Pattarn4:
			if (_Dir == eDir::R)
				_Animator->Play(L"Lupiar_Attack4_Right", false);
			else
				_Animator->Play(L"Lupiar_Attack4_Left", false);
			break;
		default:
			break;
		}
	}
	void Lupiar::afterAction()
	{
		_State = eLupiarState::Idle;
		animationCtrl();
	}
	void Lupiar::pattarn1Dash()
	{
		if (_Dash == false)
			_Dash = true;
		else
			_Dash = false;
	}
	void Lupiar::pattarn1Attack()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_MeleeAttack == nullptr)
		{
			if (_Dir == eDir::R)
			{
				_MeleeAttack = object::Instantiate<MonMeleeAttack>(pos,eLayerType::Throws);
				_MeleeAttack->GetComponent<Collider>()->Size(Vector2(40.0f * 3, 35.0f * 3));
				Vector2 size = _MeleeAttack->GetComponent<Collider>()->Size();
				Transform* cTr = _MeleeAttack->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x += size.x / 2.0f;
				cPos.y -= size.y;
				cTr->Pos(cPos);
				pattarnSound();
			}
			else
			{
				_MeleeAttack = object::Instantiate<MonMeleeAttack>(pos,eLayerType::Throws);
				_MeleeAttack->GetComponent<Collider>()->Size(Vector2(40.0f * 3, 35.0f * 3));
				Vector2 size = _MeleeAttack->GetComponent<Collider>()->Size();
				Transform* cTr = _MeleeAttack->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x -= size.x + (size.x / 2.0f);
				cPos.y -= size.y;
				cTr->Pos(cPos);
				pattarnSound();
			}
		}
		else
		{
			_MeleeAttack->State(GameObject::eState::Death);
			_MeleeAttack = nullptr;
		}
	}
	void Lupiar::pattarn2Attack()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_MeleeAttack == nullptr)
		{
			if (_Dir == eDir::R)
			{
				_MeleeAttack = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
				_MeleeAttack->GetComponent<Collider>()->Size(Vector2(35.0f * 3, 35.0f * 3));
				Vector2 size = _MeleeAttack->GetComponent<Collider>()->Size();
				Transform* cTr = _MeleeAttack->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x += size.x / 2.0f;
				cPos.y -= size.y;
				cTr->Pos(cPos);
				pattarnSound();
			}
			else
			{
				_MeleeAttack = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
				_MeleeAttack->GetComponent<Collider>()->Size(Vector2(35.0f * 3, 35.0f * 3));
				Vector2 size = _MeleeAttack->GetComponent<Collider>()->Size();
				Transform* cTr = _MeleeAttack->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x -= size.x + (size.x / 2.0f);
				cPos.y -= size.y;
				cTr->Pos(cPos);
				pattarnSound();
			}
		}
		else
		{
			_MeleeAttack->State(GameObject::eState::Death);
			_MeleeAttack = nullptr;
		}
	}
	void Lupiar::pattarn3Attack()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		Vector2 playerPos = playerTr->Pos();
		_LupiarBall = object::Instantiate<LupiarBall>(pos, eLayerType::Throws);
		_LupiarBall->StartPos(pos);
		_LupiarBall->DirVector((pos - playerPos).Normalize());
		_LupiarBall = object::Instantiate<LupiarBall>(pos+Vector2(20,0), eLayerType::Throws);
		_LupiarBall->StartPos(pos + Vector2(20, 0));
		_LupiarBall->DirVector(((pos + Vector2(20, 0)) - playerPos).Normalize());
	}
	void Lupiar::pattarn4Attack()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_MeleeAttack == nullptr)
		{
			if (_Dir == eDir::R)
			{
				_MeleeAttack = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
				_MeleeAttack->GetComponent<Collider>()->Size(Vector2(24.0f * 3, 60.0f * 3));
				Vector2 size = _MeleeAttack->GetComponent<Collider>()->Size();
				Transform* cTr = _MeleeAttack->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x += size.x / 2.0f;
				cPos.y -= size.y;
				cTr->Pos(cPos);
				pattarnSound();
			}
			else
			{
				_MeleeAttack = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
				_MeleeAttack->GetComponent<Collider>()->Size(Vector2(24.0f * 3, 60.0f * 3));
				Vector2 size = _MeleeAttack->GetComponent<Collider>()->Size();
				Transform* cTr = _MeleeAttack->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x -= size.x + (size.x / 2.0f);
				cPos.y -= size.y;
				cTr->Pos(cPos);
				pattarnSound();
			}
		}
		else
		{
			_MeleeAttack->State(GameObject::eState::Death);
			_MeleeAttack = nullptr;
		}
	}
	void Lupiar::pattarnSound()
	{
		_SoundPack[(int)eSound::pattarn]->Play(false);
	}
	void Lupiar::RollSound()
	{
		_SoundPack[(int)eSound::Roll]->Play(false);
	}
}