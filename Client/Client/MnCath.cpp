#include "MnCath.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnRigidbody.h"
#include "MnSceneManager.h"
#include "MnArsonist.h"
#include "MnTime.h"
#include "MnArrow.h"
#include "MnCollider.h"
#include "MnNpcMelee.h"
#include "MnObject.h"
namespace Mn
{
	Cath::Cath()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Collider(nullptr)
		, _Melee(nullptr)
		, _Boss(nullptr)
		, _Dir(eDir::R)
		, _NpcState(eNpcState::Idle)
		, _Ready(0)
		, _AfterAction(true)
		, _Hurt(0.0f)
	{
	}
	Cath::~Cath()
	{
	}
	void Cath::Initialize()
	{
		GameObject::SetName(L"NPC");
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(24.0f * 3, 38.0f * 3));
		_Collider->Center(Vector2(-12.0f * 3, -40.0f * 3));

		_Image = Resources::Load<Image>(L"Cath", L"..\\Resources\\cath.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Cath_Move_Right", _Image, Vector2::Zero, 8, 4, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Move_Left", _Image, Vector2(0,48), 8, 4, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Fight_Idle_Right", _Image, Vector2(0, 48*2), 8, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Fight_Idle_Left", _Image, Vector2(0, 48*3), 8, 4, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Hurt_Right", _Image, Vector2(48 * 7, 48 * 2), 8, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Hurt_Left", _Image, Vector2(48 * 7, 48 * 3), 8, 4, 1, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Cath_Attack", L"..\\Resources\\cath_Attack.bmp");
		_Animator->CreateAnimation(L"Cath_Attack_Right", _Image, Vector2::Zero, 14, 2, 14, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cath_Attack_Left", _Image, Vector2(0,48), 14, 2, 14, Vector2::Zero, 0.08);

		_Animator->GetCompleteEvent(L"Cath_Attack_Right") = std::bind(&Cath::afterAction, this);
		_Animator->GetCompleteEvent(L"Cath_Attack_Left") = std::bind(&Cath::afterAction, this);
		_Animator->FindAnimation(L"Cath_Attack_Right")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Cath::meleeAttack, this);
		_Animator->FindAnimation(L"Cath_Attack_Left")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Cath::meleeAttack, this);
		_Animator->FindAnimation(L"Cath_Attack_Right")->GetSprite(9)._Events._FrameEvent._Event = std::bind(&Cath::meleeAttackDone, this);
		_Animator->FindAnimation(L"Cath_Attack_Left")->GetSprite(9)._Events._FrameEvent._Event = std::bind(&Cath::meleeAttackDone, this);

		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> bossObj = scene->GetGameObject(eLayerType::Monster);
		for (auto v : bossObj)
		{
			if (dynamic_cast<Arsonist*>(v))
			{
				_Boss = dynamic_cast<Arsonist*>(v);
			}
		}
		_Animator->Play(L"Cath_Fight_Idle_Right", true);
		GameObject::Initialize();
	}
	void Cath::Update()
	{
		if (_Boss->GetComponent<Transform>() != nullptr)
		{
			Transform* bossTr = _Boss->GetComponent<Transform>();
			Transform* Tr = GetComponent<Transform>();
			Vector2 bossPos = bossTr->Pos();
			Vector2 pos = Tr->Pos();
			if (_AfterAction == true)
			{
				_NpcState = eNpcState::Move;
				animationCtrl();
				_AfterAction = false;
			}
			switch (_NpcState)
			{
			case eNpcState::Idle:
				idle();
				break;
			case eNpcState::Attack:
				attack();
				break;
			case eNpcState::Move:
				move();
				break;
			case eNpcState::Hurt:
				hurt();
				break;
			default:
				break;
			}
		}
		else
		{
			_NpcState = eNpcState::Idle();
			animationCtrl();
		}
		GameObject:: Update();
	}
	void Cath::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Cath::Release()
	{
		GameObject::Release();
	}
	void Cath::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"Boss" && _Hurt==0)
		{
			_NpcState = eNpcState::Hurt;
			animationCtrl();
		}

		if (other->Owner()->GetName() == L"Throws")
		{
			if (dynamic_cast<Arrow*>(other->Owner()) || dynamic_cast<NpcMelee*>(other->Owner()))
			{
			}
			else 
			{
				_NpcState = eNpcState::Hurt;
				animationCtrl();
			}
		}
	}
	void Cath::OnCollisionStay(Collider* other)
	{
	}
	void Cath::OnCollisionExit(Collider* other)
	{
	}
	void Cath::think()
	{

	}
	void Cath::idle()
	{
		_Ready += Time::DeltaTime();
		if (_Ready >= 1.5f)
		{
			_AfterAction = true;
			_Ready = 0;
		}
	}
	void Cath::move()
	{
		Transform* bossTr = _Boss->GetComponent<Transform>();
		Vector2 bossPos = bossTr->Pos();
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		float dir = bossPos.x - pos.x;
		if (dir <= 0)
		{
			_Dir = eDir::L;
			pos.x -= 50 * Time::DeltaTime();
			animationCtrl();
		}
		else
		{
			_Dir = eDir::R;
			pos.x += 50 * Time::DeltaTime();
			animationCtrl();
		}
		Tr->Pos(pos);
		if (fabs(dir) <= 150)
		{
			_NpcState = eNpcState::Attack;
			animationCtrl();
		}
	}
	void Cath::attack()
	{
	}
	void Cath::hurt()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		_Hurt += Time::DeltaTime();
		if (_Hurt < 0.7)
		{
			if (_Dir == eDir::R)
			{
				pos.x -= 100.0f * Time::DeltaTime();
				pos.y -= 100.0f * Time::DeltaTime();
			}
			else
			{
				pos.x += 100.0f * Time::DeltaTime();
				pos.y -= 100.0f * Time::DeltaTime();
			}
			Tr->Pos(pos);
		}
		if (_Hurt >= 1.5)
		{
			_NpcState = eNpcState::Idle();
			_Hurt = 0;
		}
	}
	void Cath::afterAction()
	{
		_NpcState = eNpcState::Idle;
		animationCtrl();
	}
	void Cath::animationCtrl()
	{
		switch (_NpcState)
		{
		case eNpcState::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cath_Fight_Idle_Left", true);
			else
				_Animator->Play(L"Cath_Fight_Idle_Right", true);
			break;
		case eNpcState::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cath_Attack_Right", false);
			else
				_Animator->Play(L"Cath_Attack_Left", false);
			break;
		case eNpcState::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cath_Move_Right", true);
			else
				_Animator->Play(L"Cath_Move_Left", true);
			break;
		case eNpcState::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Cath_Hurt_Right", false);
			else
				_Animator->Play(L"Cath_Hurt_Left", false);
			break;
		default:
			break;
		}
	}
	void Cath::meleeAttack()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Vector2 size = _Collider->Size();
		if (_Dir == eDir::R)
		{
			pos.y -= size.y;
			pos.x += size.x;
		}
		else
		{
			pos.y -= size.y;
			pos.x -= size.x*2;
		}
		_Melee = object::Instantiate<NpcMelee>(pos,eLayerType::Throws);
	}
	void Cath::meleeAttackDone()
	{
		_Melee->State(eState::Death);
		_Melee = nullptr;
	}
}