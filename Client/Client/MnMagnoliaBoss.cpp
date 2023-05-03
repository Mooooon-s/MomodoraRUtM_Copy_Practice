#include "MnMagnoliaBoss.h"

#include "MnImage.h"
#include "MnResources.h"

#include "MnTransform.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnAnimator.h"
#include "MnRigidbody.h"

#include "MnObject.h"
#include "MnLupiarBall.h"
#include "MnMonMeleeAttack.h"

#include "MnTime.h"

#include "MnSceneManager.h"
#include "MnKaho.h"

#include "MnHitEffect.h"
#include "MnChargeEffect.h"
#include "MnBossHpBar.h"
namespace Mn
{
	MagnoliaBoss::MagnoliaBoss()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _Kaho(nullptr)
		, _Melee(nullptr)
		, _HpBar(nullptr)
		, _State(eMagnolia::Idle)
		, _Dir(eDir::L)
		, _Timer(0.0f)
		, _Move(false)
		, _On(true)
		, _Hp(100)
	{
		Transform* Tr = GetComponent<Transform>();
		Tr->Pos(Vector2(-200, -200));
	}
	MagnoliaBoss::~MagnoliaBoss()
	{
	}
	void MagnoliaBoss::Initialize()
	{
		SetName(L"Boss");
		//√“§¡§≤ Æx

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-12.0f * 3, -35.0f * 3));
		_Collider->Size(Vector2(24.0f * 3, 35.0f * 3));

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(true);

		_Image = Resources::Load<Image>(L"MagnoliaBoss", L"..\\Resources\\Magnolia_knife.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"MagnoliaBoss_Idle_Left", _Image, Vector2::Zero, 4, 4, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"MagnoliaBoss_Idle_Right", _Image, Vector2(0,48), 4, 4, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"MagnoliaBoss_Hurt_Left", _Image, Vector2(0,48*2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"MagnoliaBoss_Hurt_Right", _Image, Vector2(0,48*3), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"MagnoliaBoss_Death_Left", _Image, Vector2(48,48*2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"MagnoliaBoss_Death_Right", _Image, Vector2(48,48*3), 4, 4, 1, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"MagnoliaBoss_Attack", L"..\\Resources\\Magnolia_knife_attack.bmp");
		_Animator->CreateAnimation(L"MagnoliaBoss_Attack_Left", _Image, Vector2::Zero, 7, 2, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"MagnoliaBoss_Attack_Right", _Image, Vector2(0,48), 7, 2, 7, Vector2::Zero, 0.08);

		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Left")->GetSprite(1)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackMove, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Right")->GetSprite(1)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackMove, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Left")->GetSprite(2)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackMove, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Right")->GetSprite(2)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackMove, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackCollider, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackCollider, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Left")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackCollider, this);
		_Animator->FindAnimation(L"MagnoliaBoss_Attack_Right")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&MagnoliaBoss::attackCollider, this);

		_Animator->Play(L"MagnoliaBoss_Idle_Left", true);
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

		_HpBar = object::Instantiate<BossHpBar>(Vector2(150, 675), eLayerType::UI);

		GameObject::Initialize();
	}
	void MagnoliaBoss::Update()
	{
		_HpBar->Hp(_Hp);
		switch (_State)
		{
		case eMagnolia::Idle:
			idle();
			break;
		case eMagnolia::Hurt:
			break;
		case eMagnolia::Attack:
			attack();
			break;
		case eMagnolia::ShowUp:
			showUp();
			break;
		case eMagnolia::Disappear:
			disappear();
			break;
		case eMagnolia::Death:
			death();
			break;
		default:
			break;
		}
		if (_Hp <= 0 && _State != eMagnolia::Death)
		{
			SceneManager::SetWall(true);
			_State = eMagnolia::Death;
			animationCtrl();
		}
		GameObject::Update();
	}
	void MagnoliaBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MagnoliaBoss::Release()
	{
		GameObject::Release();
	}
	void MagnoliaBoss::OnCollisionEnter(Collider* other)
	{
		if (_State != eMagnolia::Death)
		{
			if (other->Owner()->GetName() == L"meleeAttack")
			{
				_Hp -= 1.5;
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->Pos();
				pos.y -= (_Collider->Size().y / 2.0f);
				HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
				hitEffect->Dir((int)_Dir);
				if (_Hp <= 0)
				{
					_Collider->Size(Vector2::Zero);
					hitEffect->AnimationCntrl(0);
				}
				else
				{
					hitEffect->AnimationCntrl(2);
				}
			}
			if (other->Owner()->GetName() == L"Arrow")
			{
				_Hp -= 1;
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->Pos();
				pos.y -= (_Collider->Size().y / 2.0f);
				HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
				hitEffect->Dir((int)_Dir);
				hitEffect->AnimationCntrl(2);
			}
		}
	}
	void MagnoliaBoss::idle()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		_Timer += Time::DeltaTime();
		if (_Timer >= 2 && _On==true)
		{
			ChargeEffect* effect = object::Instantiate<ChargeEffect>(Vector2(pos.x, pos.y - (24 * 3)), eLayerType::ChargeEffect);
			effect->GetOwnerObject(this);
			_On = false;
		}
		if (_Timer >= 3)
		{
			_On = true;
			_Timer = 0;
			pos.x += _Collider->Size().x;
			LupiarBall* ball = object::Instantiate<LupiarBall>(pos,eLayerType::Throws);
			ball->DirVector(Vector2::Zero);
			pos.x -= _Collider->Size().x*2;
			LupiarBall* ball2 = object::Instantiate<LupiarBall>(pos,eLayerType::Throws);
			ball2->DirVector(Vector2::Zero);
			Transform* Tr = GetComponent<Transform>();
			Tr->Pos(Vector2(0, 900));
			_State = eMagnolia::Disappear;
			animationCtrl();
		}
	}
	void MagnoliaBoss::showUp()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (pos.y >= 671.0f)
		{
			pos.y -= 1500.0f * Time::DeltaTime();
			Tr->Pos(pos);
		}
		else
		{
			Resources::Load<Sound>(L"attack", L"..\\Resources\\Sound\\Sword.wav")->Play(false);
			_State = eMagnolia::Attack;
			animationCtrl();
		}
	}
	void MagnoliaBoss::attack()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Move == true)
		{
			if (_Dir == eDir::R)
				pos.x += 50.0f * Time::DeltaTime();
			else
				pos.x -= 50.0f * Time::DeltaTime();
		}
		Tr->Pos(pos);
	}
	void MagnoliaBoss::death()
	{
		_Timer += Time::DeltaTime();
		if (_Timer >= 2)
		{
			this->State(eState::Death);
			_HpBar->State(eState::Death);
			SceneManager::StopSound(L"Boss3_BG");
		}
	}
	void MagnoliaBoss::disappear()
	{
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		Transform* Tr = GetComponent<Transform>();
		Vector2 playerPos = playerTr->Pos();
		Vector2 pos = Vector2::Zero;
		
		_Timer += Time::DeltaTime();
		if (_Timer >= 2)
		{
			//R=0 L=1
			if (_Kaho->KahoDir() == 0)
			{
				Vector2 movePos = _Kaho->KahoColliderSize() / 2.0f + Vector2(50, 0);
				pos= playerPos - movePos;
				_Dir = eDir::R;
				Tr->Pos(Vector2(pos.x, 900.0f));
			}
			else
			{
				Vector2 movePos = _Kaho->KahoColliderSize() / 2.0f + Vector2(50, 0);
				pos = playerPos + movePos;
				_Dir = eDir::L;
				Tr->Pos(Vector2( pos.x, 900.0f));
			}
			_Timer = 0;
			Resources::Load<Sound>(L"ShowUp", L"..\\Resources\\Sound\\SwordAppear.wav")->Play(false);
			_State = eMagnolia::ShowUp;
			animationCtrl();
		}
	}
	void MagnoliaBoss::attackMove()
	{
		if (_Move == false)
			_Move = true;
		else
			_Move = true;
	}
	void MagnoliaBoss::attackCollider()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Melee == nullptr)
		{
			if (_Dir == eDir::R)
			{
				_Melee = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
				_Melee->GetComponent<Collider>()->Size(Vector2(40.0f * 3, 35.0f * 3));
				Vector2 size = _Melee->GetComponent<Collider>()->Size();
				Transform* cTr = _Melee->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x += size.x / 2.0f;
				cPos.y -= size.y;
				cTr->Pos(cPos);
			}
			else
			{
				_Melee = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
				_Melee->GetComponent<Collider>()->Size(Vector2(40.0f * 3, 35.0f * 3));
				Vector2 size = _Melee->GetComponent<Collider>()->Size();
				Transform* cTr = _Melee->GetComponent<Transform>();
				Vector2 cPos = cTr->Pos();
				cPos.x -= size.x + (size.x / 2.0f);
				cPos.y -= size.y;
				cTr->Pos(cPos);
			}
		}
		else
		{
			_Melee->State(eState::Death);
			_Melee = nullptr;
			_State = eMagnolia::Idle;
			animationCtrl();
		}
	}
	void MagnoliaBoss::animationCtrl()
	{
		switch (_State)
		{
		case eMagnolia::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"MagnoliaBoss_Idle_Right", true);
			else
				_Animator->Play(L"MagnoliaBoss_Idle_Left", true);
			break;
		case eMagnolia::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"MagnoliaBoss_Hurt_Right", false);
			else
				_Animator->Play(L"MagnoliaBoss_Hurt_Left", false);
			break;
		case eMagnolia::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"MagnoliaBoss_Attack_Right", false);
			else
				_Animator->Play(L"MagnoliaBoss_Attack_Left", false);
			break;
		case eMagnolia::ShowUp:
			if (_Dir == eDir::R)
				_Animator->Play(L"MagnoliaBoss_Idle_Right", true);
			else
				_Animator->Play(L"MagnoliaBoss_Idle_Left", true);
			break;
		case eMagnolia::Disappear:
			if (_Dir == eDir::R)
				_Animator->Play(L"MagnoliaBoss_Idle_Right", true);
			else
				_Animator->Play(L"MagnoliaBoss_Idle_Left", true);
			break;
		case eMagnolia::Death:
			if (_Dir == eDir::R)
				_Animator->Play(L"MagnoliaBoss_Death_Right", true);
			else
				_Animator->Play(L"MagnoliaBoss_Death_Left", true);
			break;
		default:
			break;
		}
	}
}