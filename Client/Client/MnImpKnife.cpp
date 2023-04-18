#include "MnImpKnife.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnResources.h"
#include "MnRigidbody.h"
#include "MnTransform.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnKaho.h"
#include "MnKnife.h"
#include "MnObject.h"
#include "MnHitEffect.h"

namespace Mn
{
	ImpKnife::ImpKnife()
		: GameObject()
		, _MonState(eMonStatus::Idle)
		, _Dir(eDir::R)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _Animator(nullptr)
		, _Image(nullptr)
		, _kaho(nullptr)
		, _Pos(Vector2::Zero)
		, _ThinkTime(0.0f)
		, _Hp(1.0f)
		, _ActionCount(0)
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(-100, -100));
	}
	ImpKnife::~ImpKnife()
	{
	}
	void ImpKnife::Initialize()
	{
		GameObject::SetName(L"Enemy");

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-10 * 3, -20 * 3));
		_Collider->Size(Vector2(20 * 3, 20 * 3));

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Image = Resources::Load<Image>(L"Imp_Knife", L"..\\Resources\\Imp_2.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Imp_Knife_Idle_Right", _Image, Vector2::Zero, 10, 5, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Idle_Left", _Image, Vector2(32,0), 10, 5, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Hurt_Right", _Image, Vector2(32*2,0), 10, 5, 1, Vector2::Zero, 1);
		_Animator->CreateAnimation(L"Imp_Knife_Hurt_Left", _Image, Vector2(32*3,0), 10, 5, 1, Vector2::Zero, 1);
		_Animator->CreateAnimation(L"Imp_Knife_Jump_Right", _Image, Vector2(0,32), 10, 5, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Jump_Left", _Image, Vector2(0,32*2), 10, 5, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Fall_Right", _Image, Vector2(32*3,32), 10, 5, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Fall_Left", _Image, Vector2(32*3,32*2), 10, 5, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Attack_Right", _Image, Vector2(0,32*3), 10, 5, 10, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Knife_Attack_Left", _Image, Vector2(0,32*4), 10, 5, 10, Vector2::Zero, 0.08);

		_Animator->FindAnimation(L"Imp_Knife_Attack_Right")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&ImpKnife::trowKnife, this);
		_Animator->FindAnimation(L"Imp_Knife_Attack_Left")->GetSprite(5)._Events._FrameEvent._Event = std::bind(&ImpKnife::trowKnife, this);
		
		
		_Animator->Play(L"Imp_Knife_Idle_Right",true);
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> playerobj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerobj)
		{
			if (dynamic_cast<Kaho*>(v))
				_kaho = dynamic_cast<Kaho*>(v);
		}
		GameObject::Initialize();
	}
	void ImpKnife::Update()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos = tr->Pos();
		_ThinkTime += Time::DeltaTime();
		if (_ThinkTime >= 0.8 && _Rigidbody->GetGround()==true && _Hp>0)
		{
			think();
			_ThinkTime = 0;
		}
		switch (_MonState)
		{
		case eMonStatus::Move:
			move();
			break;
		case eMonStatus::Attack:
			attack();
			break;
		case eMonStatus::Idle:
			idle();
			break;
		case eMonStatus::Hurt:
			hurt();
			break;
		case eMonStatus::Fall:
			fall();
			break;
		default:
			break;
		}
		tr->Pos(_Pos);
		GameObject::Update();
	}
	void ImpKnife::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ImpKnife::Release()
	{
		GameObject::Release();
	}
	void ImpKnife::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(0);
			_MonState = eMonStatus::Hurt;
			animatorCntrl();
			_Hp -= 1.5f;
			_ThinkTime = 0;
		}

		if (other->Owner()->GetName() == L"Arrow")
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(2);
			_MonState = eMonStatus::Hurt;
			animatorCntrl();
			_Hp -= 1.0f;
			_ThinkTime = 0;
		}
	}
	void ImpKnife::OnCollisionStay(Collider* other)
	{
	}
	void ImpKnife::OnCollisionExit(Collider* other)
	{
	}
	void ImpKnife::think()
	{
		Vector2 playerPos = _kaho->CameraTarget<GameObject>()->GetComponent<Transform>()->Pos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		float distX = pos.x - playerPos.x;
		if (distX < 0)
			_Dir = eDir::R;
		else
			_Dir = eDir::L;
		if (_ActionCount > 3)
		{
			_ActionCount = 0;
			_MonState = eMonStatus::Attack;
			animatorCntrl();
		}
		else
		{
			_ActionCount++;
			Vector2 velocity = _Rigidbody->Velocity();
			velocity.y = 0;
			velocity.y -= 500.0;
			_Rigidbody->Velocity(velocity);
			_Rigidbody->SetGround(false);
			_MonState = eMonStatus::Move;
			animatorCntrl();
		}
	}
	void ImpKnife::move()
	{
		Vector2 playerPos = _kaho->CameraTarget<GameObject>()->GetComponent<Transform>()->Pos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		float distX = pos.x - playerPos.x;
		if (fabs(distX) < 150)
		{
			if (_Dir == eDir::R)
			{
				_Pos.x -= 100.0f * Time::DeltaTime();
			}
			else
			{
				_Pos.x += 100.0f * Time::DeltaTime();
			}
		}
		if (fabs(distX) > 150)
		{
			if (_Dir == eDir::R)
			{
				_Pos.x += 100.0f * Time::DeltaTime();
			}
			else
			{
				_Pos.x -= 100.0f * Time::DeltaTime();
			}
		}
		if (fabs(distX) == 150)
		{
			_MonState = eMonStatus::Idle;
			animatorCntrl();
		}

		Vector2 velocity = GetComponent<Rigidbody>()->Velocity();
		if (velocity.y > 0)
		{
			_MonState = eMonStatus::Fall;
			animatorCntrl();
		}

	}
	void ImpKnife::attack()
	{
	}
	void ImpKnife::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_Hp <= 0.0f && _HurtTime>=0.7)
		{
			this->State(eState::Death);
		}
	}
	void ImpKnife::fall()
	{
		if (_Rigidbody->GetGround() == true)
		{
			_MonState = eMonStatus::Idle;
			animatorCntrl();
		}
	}
	void ImpKnife::idle()
	{

	}
	void ImpKnife::animatorCntrl()
	{
		switch (_MonState)
		{
		case eMonStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Knife_Jump_Right", false);
			else
				_Animator->Play(L"Imp_Knife_Jump_Left", false);
			break;
		case eMonStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Knife_Attack_Right", false);
			else
				_Animator->Play(L"Imp_Knife_Attack_Left", false);
			break;
		case eMonStatus::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Knife_Jump_Right", false);
			else
				_Animator->Play(L"Imp_Knife_Jump_Left", false);
			break;
		case eMonStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Knife_Hurt_Right", false);
			else
				_Animator->Play(L"Imp_Knife_Hurt_Left", false);
			break;
		case eMonStatus::Fall:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Knife_Fall_Right", false);
			else
				_Animator->Play(L"Imp_Knife_Fall_Left", false);
			break;
		default:
			break;
		}
	}
	void ImpKnife::trowKnife()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		pos.y -= _Collider->Size().y / 2.0f;
		if (_Dir == eDir::R)
		{
			pos.x += (_Collider->Size().x / 2.0f);
			Knife* knife = object::Instantiate<Knife>(pos, eLayerType::Throws);
			knife->DirR();
		}
		else
		{
			pos.x -= (_Collider->Size().x / 2.0f);
			Knife* knife = object::Instantiate<Knife>(pos, eLayerType::Throws);
			knife->DirL();
		}
	}
}