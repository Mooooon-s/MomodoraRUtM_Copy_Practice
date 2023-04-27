#include "MnBigPlant.h"
#include "MnResources.h"
#include "MnAnimator.h"
#include "MnComponent.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnHitEffect.h"
#include "MnTransform.h"
#include "MnObject.h"
#include "MnCollider.h"
#include "MnTime.h"
#include "MnRigidbody.h"
#include "MnMonMeleeAttack.h"

namespace Mn
{
	BigPlant::BigPlant()
		: GameObject()
		, _Rigidbody(nullptr)
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Dir(eDir::R)
		, _MonState(eMonStats::Idle)
		, _Kaho(nullptr)
		, _Hp(30)
		, _Timer(0.0f)
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(-100*3, -100*3));
	}
	BigPlant::~BigPlant()
	{
	}
	void BigPlant::Initialize()
	{
		SetName(L"Enemy");
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(60*3, 60*3));
		_Collider->Center(Vector2(-30*3, -60*3));
		_Image = Resources::Load<Image>(L"Big_Plant", L"..\\Resources\\Big.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Big_Plant_Idle_Right", _Image, Vector2::Zero, 16, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Big_Plant_Idle_Left", _Image, Vector2(0,100), 16, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Big_Plant_Attack_Right", _Image, Vector2(0,100*2), 16, 4, 16, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Big_Plant_Attack_Left", _Image, Vector2(0,100*3), 16, 4, 16, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Big_Plant_Move", L"..\\Resources\\Big_Move.bmp");
		_Animator->CreateAnimation(L"Big_Plant_Move_Right", _Image, Vector2::Zero, 10, 2, 10, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Big_Plant_Move_Left", _Image, Vector2(0,100), 10, 2, 10, Vector2::Zero, 0.08);
		_Animator->Play(L"Big_Plant_Idle_Right", true);

		_Animator->GetCompleteEvent(L"Big_Plant_Attack_Right") = std::bind(&BigPlant::afterAttack, this);
		_Animator->GetCompleteEvent(L"Big_Plant_Attack_Left") = std::bind(&BigPlant::afterAttack, this);

		_Animator->FindAnimation(L"Big_Plant_Attack_Right")->GetSprite(8)._Events._FrameEvent._Event = std::bind(&BigPlant::beforAttack, this);
		_Animator->FindAnimation(L"Big_Plant_Attack_Left")->GetSprite(8)._Events._FrameEvent._Event = std::bind(&BigPlant::beforAttack, this);
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
		GameObject::Initialize();
	}
	void BigPlant::Update()
	{
		switch (_MonState)
		{
		case eMonStats::Idle:
			idle();
			break;
		case eMonStats::Attack:
			attack();
			break;
		case eMonStats::Move:
			move();
			break;
		case eMonStats::Death:
			death();
			break;
		default:
			break;
		}

		if (_Hp <= 0)
		{
			SceneManager::SetWall(true);
			_MonState = eMonStats::Death;
		}

		GameObject::Update();
	}
	void BigPlant::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BigPlant::Release()
	{
		GameObject::Release();
	}
	void BigPlant::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			_Hp -= 2;
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(0);
		}
		if (other->Owner()->GetName() == L"Arrow")
		{
			_Hp -= 1;
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(2);
		}
	}
	void BigPlant::OnCollisionStay(Collider* other)
	{
	}
	void BigPlant::OnCollisionExit(Collider* other)
	{
	}
	void BigPlant::idle()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		float distX = Tr->Pos().x - playerTr->Pos().x;
		float distY = Tr->Pos().y - playerTr->Pos().y;
		if (fabs(distX) <= 800 && (distY <= 90 && distY >= -90))
		{
			_MonState = eMonStats::Move;
			animatorCntrl();
		}
	}
	void BigPlant::move()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		float distX = Tr->Pos().x - playerTr->Pos().x;
		float distY = Tr->Pos().y - playerTr->Pos().y;
		Vector2 pos = Tr->Pos();

		if (distX <= 0 && distY >= -90 && distY < 90)
		{
			_Dir = eDir::R;
			animatorCntrl();
			pos.x += 50 * Time::DeltaTime();
		}
		if (distX > 0 && distY >= -90 && distY < 90)
		{
			_Dir = eDir::L;
			animatorCntrl();
			pos.x -= 50* Time::DeltaTime();
		}
		if (fabs(distX) <= 200 && distY <= 90)
		{
			_MonState = eMonStats::Attack;
			animatorCntrl();
		}

		Tr->Pos(pos);
	}
	void BigPlant::attack()
	{
	}
	void BigPlant::death()
	{
		_Timer += Time::DeltaTime();
		if (_Timer >= 1.5)
			this->State(eState::Death);
		if (_Dir == eDir::R)
			_Animator->Play(L"Big_Plant_Idle_Right", true);
		else
			_Animator->Play(L"Big_Plant_Idle_Left", true);
	}
	void BigPlant::animatorCntrl()
	{
		switch (_MonState)
		{
		case eMonStats::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Big_Plant_Idle_Right",true);
			else
				_Animator->Play(L"Big_Plant_Idle_Left",true);
			break;
		case eMonStats::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Big_Plant_Attack_Right", false);
			else
				_Animator->Play(L"Big_Plant_Attack_Left", false);
			break;
		case eMonStats::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Big_Plant_Move_Right", true);
			else
				_Animator->Play(L"Big_Plant_Move_Left", true);
			break;
		default:
			break;
		}
	}
	void BigPlant::beforAttack()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Dir == eDir::R)
		{
			MonMeleeAttack* coll = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
			coll->GetComponent<Collider>()->Size(Vector2(60*3,50*3));
			Vector2 size = coll->GetComponent<Collider>()->Size();
			Transform* cTr = coll->GetComponent<Transform>();
			Vector2 cPos = cTr->Pos();
			cPos.x += size.x / 2.0f;
			cPos.y -= size.y;
			cTr->Pos(cPos);
		}
		else
		{
			MonMeleeAttack* coll = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
			coll->GetComponent<Collider>()->Size(Vector2(60 * 3, 50 * 3));
			Vector2 size = coll->GetComponent<Collider>()->Size();
			Transform* cTr = coll->GetComponent<Transform>();
			Vector2 cPos = cTr->Pos();
			cPos.x -= (size.x + size.x / 2.0f);
			cPos.y -= size.y;
			cTr->Pos(cPos);
		}
	}
	void BigPlant::afterAttack()
	{
		_MonState = eMonStats::Idle();
		animatorCntrl();
	}
}