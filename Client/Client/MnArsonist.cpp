#include "MnArsonist.h"
#include "MnResources.h"
#include "MnTime.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnKaho.h"
#include "MnSceneManager.h"
#include "MnObject.h"
#include "MnMonMeleeAttack.h"
#include "MnHitEffect.h"
#include "MnFireBall.h"
#include "MnFlame.h"
#include "MnFireFlame.h"
#include "MnChargeEffect.h"
namespace Mn
{
	Arsonist::Arsonist()
		: _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Collider(nullptr)
		, _MonStatus(eMonStatus::Idle)
		, _Dir(eDir::R)
		, _time(0)
		, _afterAction(true)
		, _Teleporting(false)
		, _Kaho(nullptr)
		, _Count(0)
		, _HurtTime(0.0f)
		, _KnockBack(15.0f)
		, _FireBall(nullptr)
		, _FireFlame(nullptr)
		, _Ready(0)
	{
	}
	Arsonist::~Arsonist()
	{
	}
	void Arsonist::Initialize()
	{
		GameObject::SetName(L"Boss");

		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(400.0f, 400.0f));
		_Animator = AddComponent<Animator>();

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-12.0f*3,-35.0f*3));
		_Collider->Size(Vector2(24.0f*3, 35.0f*3));

		_Image = Resources::Load<Image>(L"Arsonist", L"..\\Resources\\Arsonist_Move.bmp");
		_Animator->CreateAnimation(L"walk_Left", _Image, Vector2::Zero, 13, 15,7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"walk_Right", _Image, Vector2(0,64), 13, 15, 7, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Back_Step_Left", _Image, Vector2(0,64*2), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Back_Step_Right", _Image, Vector2(0,64*3), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"to_Charge_Left", _Image, Vector2(0, 64 * 4), 13, 15, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"to_Charge_Right", _Image, Vector2(0, 64 * 5), 13, 15, 3, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Charge_Left", _Image, Vector2(0, 64 * 6), 13, 15, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Charge_Right", _Image, Vector2(0, 64 * 7), 13, 15, 4, Vector2::Zero, 0.08);
		//pattarn1
		_Animator->CreateAnimation(L"Fire_Left", _Image, Vector2(0, 64 * 8), 13, 15, 12, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Fire_Right", _Image, Vector2(0, 64 * 9), 13, 15, 12, Vector2::Zero, 0.08);
		//hurt
		_Animator->CreateAnimation(L"Hurt_Left", _Image, Vector2(0, 64 * 10), 13, 15, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Hurt_Right", _Image, Vector2(48, 64 * 10), 13, 15, 1, Vector2::Zero, 0.08);
		//pattarn2,3
		_Animator->CreateAnimation(L"stab_Left", _Image, Vector2(0, 64 * 11), 13, 15, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"stab_Right", _Image, Vector2(0, 64 * 12), 13, 15, 11, Vector2::Zero, 0.08);
		//pattarn2,3
		_Animator->CreateAnimation(L"stab_Ball_Left", _Image, Vector2(0, 64 * 11), 13, 15, 11, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"stab_Ball_Right", _Image, Vector2(0, 64 * 12), 13, 15, 11, Vector2::Zero, 0.08);
		//idle
		_Animator->CreateAnimation(L"Idle_Left", _Image, Vector2(0, 64 * 13), 13, 15, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Idle_Right", _Image, Vector2(0, 64 * 14), 13, 15, 6, Vector2::Zero, 0.08);
		
		_Image = Resources::Load<Image>(L"Idle_Right", L"..\\Resources\\Arsonist_Attack.bmp");
		_Animator->CreateAnimation(L"Swip_Left", _Image, Vector2::Zero, 15, 2, 14,Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Swip_Right", _Image, Vector2(0,64), 15, 2, 14, Vector2::Zero, 0.08);
		_Animator->Play(L"Idle_Right",true);

		_Animator->FindAnimation(L"Swip_Left")->GetSprite(10)._Events._FrameEvent._Event = std::bind(&Arsonist::beforeAttack, this);
		_Animator->FindAnimation(L"Swip_Right")->GetSprite(10)._Events._FrameEvent._Event = std::bind(&Arsonist::beforeAttack, this);
		_Animator->FindAnimation(L"Fire_Left")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Arsonist::fire, this);
		_Animator->FindAnimation(L"Fire_Right")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Arsonist::fire, this);
		_Animator->FindAnimation(L"Fire_Left")->GetSprite(8)._Events._FrameEvent._Event = std::bind(&Arsonist::fire, this);
		_Animator->FindAnimation(L"Fire_Right")->GetSprite(8)._Events._FrameEvent._Event = std::bind(&Arsonist::fire, this);
		_Animator->FindAnimation(L"Fire_Left")->GetSprite(10)._Events._FrameEvent._Event = std::bind(&Arsonist::fire, this);
		_Animator->FindAnimation(L"Fire_Right")->GetSprite(10)._Events._FrameEvent._Event = std::bind(&Arsonist::fire, this);
		_Animator->FindAnimation(L"stab_Right")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Arsonist::makeFlame, this);
		_Animator->FindAnimation(L"stab_Left")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Arsonist::makeFlame, this);
		_Animator->FindAnimation(L"stab_Ball_Right")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Arsonist::makeFireBall, this);
		_Animator->FindAnimation(L"stab_Ball_Left")->GetSprite(6)._Events._FrameEvent._Event = std::bind(&Arsonist::makeFireBall, this);

		_Animator->GetCompleteEvent(L"Swip_Right") = std::bind(&Arsonist::afterAttack, this);
		_Animator->GetCompleteEvent(L"Swip_Left") = std::bind(&Arsonist::afterAttack, this);
		_Animator->GetCompleteEvent(L"Fire_Left") = std::bind(&Arsonist::waitTeleport, this);
		_Animator->GetCompleteEvent(L"Fire_Right") = std::bind(&Arsonist::waitTeleport, this);
		_Animator->GetCompleteEvent(L"stab_Left") = std::bind(&Arsonist::afterAttack, this);
		_Animator->GetCompleteEvent(L"stab_Right") = std::bind(&Arsonist::afterAttack, this);
		_Animator->GetCompleteEvent(L"stab_Ball_Right") = std::bind(&Arsonist::afterAttack, this);
		_Animator->GetCompleteEvent(L"stab_Ball_Left") = std::bind(&Arsonist::afterAttack, this);


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
		think();
		GameObject::Initialize();
	}
	void Arsonist::Update()
	{
		if (_afterAction==true)
		{
			think();
			_afterAction = false;
		}

		switch (_MonStatus)
		{
		case eMonStatus::Idle:
			idle();
			break;
		case eMonStatus::Move:
			move();
			break;
		case eMonStatus::Attack:
			attack();
			break;
		case eMonStatus::Hurt:
			hurt();
			break;
		case eMonStatus::Pattarn1:
			pattarn1();
			break;
		case eMonStatus::Pattarn2:
			pattarn2();
			break;
		case eMonStatus::Pattarn3:
			pattarn3();
			break;
		case eMonStatus::BackStep:
			backStep();
			break;
		default:
			break;
		}

		if(_HurtTime==0)
			_KnockBack += Time::DeltaTime();

		if (_Count >= 2 && _KnockBack>=15.0f)
		{
			_afterAction = false;
			_MonStatus = eMonStatus::Hurt;
			animationCtrl();
			_KnockBack = 0;
		}
		GameObject::Update();
	}
	void Arsonist::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Arsonist::Release()
	{
		GameObject::Release();
	}

	void Arsonist::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			pos.y -= (_Collider->Size().y / 2.0f);
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(0);
			if (_KnockBack >= 15.0f)
				_Count++;
		}
		if (other->Owner()->GetName() == L"Arrow")
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			pos.y -=(_Collider->Size().y/2.0f);
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(2);
		}
	}

	void Arsonist::OnCollisionStay(Collider* other)
	{
	}

	void Arsonist::OnCollisionExit(Collider* other)
	{
	}

	void Arsonist::animationCtrl()
	{
		switch (_MonStatus)
		{
		case eMonStatus::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Idle_Right", true);
			else
				_Animator->Play(L"Idle_Left", true);
			break;
		case eMonStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"walk_Right", true);
			else
				_Animator->Play(L"walk_Left", true);
			break;
		case eMonStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Swip_Right", false);
			else
				_Animator->Play(L"Swip_Left", false);
			break;
		case eMonStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Hurt_Right", true);
			else
				_Animator->Play(L"Hurt_Left", true);
			break;
		case eMonStatus::Pattarn1:
			if (_Dir == eDir::R)
				_Animator->Play(L"Fire_Right", false);
			else
				_Animator->Play(L"Fire_Left", false);
			break;
		case eMonStatus::Pattarn2:
			if (_Dir == eDir::R)
				_Animator->Play(L"stab_Right", false);
			else
				_Animator->Play(L"stab_Left", false);
			break;
		case eMonStatus::Pattarn3:
			if (_Dir == eDir::R)
				_Animator->Play(L"stab_Ball_Left", false);
			else
				_Animator->Play(L"stab_Ball_Right", false);
			break;
		case eMonStatus::BackStep:
			if (_Dir == eDir::R)
				_Animator->Play(L"Back_Step_Right", false);
			else
				_Animator->Play(L"Back_Step_Left", false);
			break;
		default:
			break;
		}
	}

	void Arsonist::think()
	{

		Transform* Tr = this->GetComponent<Transform>();
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		float distX = Tr->Pos().x - playerTr->Pos().x;
		float distY = Tr->Pos().y - playerTr->Pos().y;
		Vector2 pos = Tr->Pos();
		
		ChargeEffect* effect = object::Instantiate<ChargeEffect>(Vector2(pos.x, pos.y - (24 * 3)), eLayerType::ChargeEffect);
		effect->GetOwnerObject(this);
		
		if (distX <= 0)
		{
			_Dir = eDir::R;
			animationCtrl();
		}
		if (distX > 0)
		{
			_Dir = eDir::L;
			animationCtrl();
		}
		int think=0;
		if (fabs(distX) >= 400)
			think = 0;
		if (fabs(distX) < 400 && fabs(distX) >= 300)
			think = rand() % 2+4;
		if (fabs(distX) < 300 && fabs(distX) >= 0)
			think = rand() % 3+1;

		switch (think)
		{
		case 0:
			_MonStatus = eMonStatus::Pattarn1;
			animationCtrl();
			break;
		case 1:
			_MonStatus = eMonStatus::Pattarn2;
			animationCtrl();
			break;
		case 2:
			_MonStatus = eMonStatus::Pattarn3;
			animationCtrl();
			break;
		case 3:
			_MonStatus = eMonStatus::Attack;
			animationCtrl();
			break;
		case 4:
			_MonStatus = eMonStatus::Move;
			animationCtrl();
			break;
		case 5:
			_MonStatus = eMonStatus::BackStep;
			animationCtrl();
			break;
		default:
			break;
		}
	}
	void Arsonist::idle()
	{
		_Ready += Time::DeltaTime();
		if (_Ready >= 1.5f)
		{
			_afterAction=true;
			_Ready = 0;
		}
	}
	void Arsonist::move()
	{
		_Ready += Time::DeltaTime();
		if (_Ready >= 0.5f)
		{
			_MonStatus = eMonStatus::Idle;
			_Ready = 0;
			animationCtrl();
		}
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Dir == eDir::R)
		{
			pos.x += 50 * Time::DeltaTime();
		}
		else
		{
			pos.x -= 50 * Time::DeltaTime();
		}
		Tr->Pos(pos);
	}
	void Arsonist::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime >= 1.0f)
		{
			_MonStatus = eMonStatus::Idle;
			_Count = 0;
			_HurtTime = 0;
		}
	}
	void Arsonist::attack()
	{
	}
	void Arsonist::pattarn1()
	{
		//fireball
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Teleporting == true)
		{
			object::Instantiate<Flame>(Vector2(_TeleportPos.x-50, pos.y), eLayerType::Throws);
			object::Instantiate<Flame>(Vector2(_TeleportPos.x+50, pos.y), eLayerType::Throws);
			object::Instantiate<Flame>(Vector2(_TeleportPos.x, pos.y), eLayerType::Throws);
			_Teleporting = false;
			_FireBall = nullptr;
			Tr->Pos(Vector2(_TeleportPos.x,pos.y));
			_MonStatus = eMonStatus::Idle;
			animationCtrl();
		}
	}
	void Arsonist::pattarn2()
	{
		//make Flame
	}
	void Arsonist::pattarn3()
	{
		// make FireBall

	}
	void Arsonist::backStep()
	{
		_Ready += Time::DeltaTime();
		if (_Ready >= 0.3f)
		{
			_MonStatus = eMonStatus::Idle;
			_Ready = 0;
			animationCtrl();
		}
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Dir == eDir::R)
		{
			pos.x -= 500 * Time::DeltaTime();
		}
		else
		{
			pos.x += 500 * Time::DeltaTime();
		}
		Tr->Pos(pos);
	}
	void Arsonist::beforeAttack()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Dir == eDir::R)
		{
			MonMeleeAttack* coll = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
			coll->GetComponent<Collider>()->Size(Vector2(60 * 3, 35 * 3));
			Vector2 size = coll->GetComponent<Collider>()->Size();
			Transform* cTr = coll->GetComponent<Transform>();
			Vector2 cPos = cTr->Pos();
			cPos.x += size.x / 2.0f-10;
			cPos.y -= size.y;
			cTr->Pos(cPos);
		}
		else
		{
			MonMeleeAttack* coll = object::Instantiate<MonMeleeAttack>(pos, eLayerType::Throws);
			coll->GetComponent<Collider>()->Size(Vector2(60 * 3, 35 * 3));
			Vector2 size = coll->GetComponent<Collider>()->Size();
			Transform* cTr = coll->GetComponent<Transform>();
			Vector2 cPos = cTr->Pos();
			cPos.x -= (size.x + size.x / 2.0f)+10;
			cPos.y -= size.y;
			cTr->Pos(cPos);
		}
	}
	void Arsonist::afterAttack()
	{
		_MonStatus = eMonStatus::Idle;
		animationCtrl();
	}
	void Arsonist::fire()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Vector2 size = _Collider->Size();
		Vector2 cPos = Vector2::Zero;
		if(_Dir==eDir::R)
			cPos = Vector2(pos.x - size.x, pos.y - size.y / 2.0);
		else
			cPos = Vector2(pos.x + size.x, pos.y - size.y / 2.0);
		_TeleportPos = _Kaho->GetComponent<Transform>()->Pos();
		if (_FireBall == nullptr)
		{
			_FireBall = object::Instantiate<FireBall>(cPos,eLayerType::Throws);
			_FireBall->First();
		}
		else
		{
			_FireBall = object::Instantiate<FireBall>(cPos,eLayerType::Throws);
		}
		_FireBall->PlayerPos(_TeleportPos);
	}
	void Arsonist::waitTeleport()
	{
		if (_Dir == eDir::R)
			_Animator->Play(L"Idle_Right", true);
		else
			_Animator->Play(L"Idle_Left", true);
	}
	void Arsonist::makeFlame()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		object::Instantiate<Flame>(Vector2(pos.x - 70, pos.y), eLayerType::Throws);
		object::Instantiate<Flame>(Vector2(pos.x + 70, pos.y), eLayerType::Throws);
		object::Instantiate<Flame>(Vector2(pos.x, pos.y), eLayerType::Throws);
	}
	void Arsonist::makeFireBall()
	{
		Transform* Tr = this->GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Vector2 size = GetComponent<Collider>()->Size();
		_FireFlame = object::Instantiate<FireFlame>(Vector2(pos.x-(size.x/2.0f),pos.y-(size.y+size.y/2.0f)),eLayerType::Throws);
		_FireFlame->Dir(Vector2(-100, 0));
		_FireFlame = object::Instantiate<FireFlame>(Vector2(pos.x - (size.x / 2.0f), pos.y - (size.y + size.y / 2.0f)), eLayerType::Throws);
		_FireFlame->Dir(Vector2(100, 0));
	}
}
