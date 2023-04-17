#include "MnImpBomb.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnObject.h"
#include "MnBomb.h"

#include "MnSceneManager.h"
#include "MnScene.h"
#include "MnKaho.h"

#include "MnHitEffect.h"

namespace Mn
{
	ImpBomb::ImpBomb()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _Dir(eDir::R)
		, _ThinkTime(0.0f)
		, _HurtTime(0.0f)
		, _Hp(1.0f)
		, _Ishurt(false)
	{
	}
	ImpBomb::~ImpBomb()
	{
	}
	void ImpBomb::Initialize()
	{
		SetName(L"Enemy");

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-10 * 3, -20 * 3));
		_Collider->Size(Vector2(20 * 3, 20 * 3));

		_Image = Resources::Load<Image>(L"ImpBomb", L"..\\Resources\\Imp_3.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Imp_Bomb_Idle_Right", _Image, Vector2::Zero, 9, 5, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Bomb_Idle_Left", _Image, Vector2(32,0), 9, 5, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Bomb_Hurt_Right", _Image, Vector2(32*2,0), 9, 5, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Bomb_Hurt_Left", _Image, Vector2(32*3,0), 9, 5, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Bomb_Attack_Right", _Image, Vector2(0,32*3), 9, 5, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Imp_Bomb_Attack_Left", _Image, Vector2(0,32*4), 9, 5, 9, Vector2::Zero, 0.08);

		_Animator->GetCompleteEvent(L"Imp_Bomb_Attack_Right") = std::bind(&ImpBomb::afterAction, this);
		_Animator->GetCompleteEvent(L"Imp_Bomb_Attack_Left") = std::bind(&ImpBomb::afterAction, this);

		_Animator->FindAnimation(L"Imp_Bomb_Attack_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&ImpBomb::attack, this);
		_Animator->FindAnimation(L"Imp_Bomb_Attack_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&ImpBomb::attack, this);

		_Animator->Play(L"Imp_Bomb_Idle_Right", true);
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> playerobj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerobj)
		{
			if (dynamic_cast<Kaho*>(v))
				_kaho = dynamic_cast<Kaho*>(v);
		}


	}
	void ImpBomb::Update()
	{
		_ThinkTime += Time::DeltaTime();
		Vector2 playerPos = _kaho->CameraTarget<GameObject>()->GetComponent<Transform>()->Pos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		float distX = pos.x - playerPos.x;
		
		if (distX <= 0)
			_Dir = eDir::R;
		else
			_Dir = eDir::L;

		if (_ThinkTime >= 3 && _Ishurt==false)
		{
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Bomb_Attack_Right", false);
			else
				_Animator->Play(L"Imp_Bomb_Attack_Left", false);
			_ThinkTime = 0;
		}
		if (_Ishurt == true)
		{
			_HurtTime += Time::DeltaTime();
			if (_Hp <= 0 && _HurtTime >= 0.8)
			{
				this->State(eState::Death);
			}
		}
		GameObject::Update();
	}
	void ImpBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ImpBomb::Release()
	{
		GameObject::Release();
	}
	void ImpBomb::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos, eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(0);
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Bomb_Hurt_Right", false);
			else
				_Animator->Play(L"Imp_Bomb_Hurt_Left", false);
			_Hp -= 1.5f;
			_Ishurt = true;
			_ThinkTime = 0;
		}

		if (other->Owner()->GetName() == L"Arrow")
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			HitEffect* hitEffect = object::Instantiate<HitEffect>(pos,eLayerType::Effect);
			hitEffect->Dir((int)_Dir);
			hitEffect->AnimationCntrl(2);
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Bomb_Hurt_Right", false);
			else
				_Animator->Play(L"Imp_Bomb_Hurt_Left", false);
			_Hp -= 1.0f;
			_Ishurt = true;
			_ThinkTime = 0;
		}
	}
	void ImpBomb::OnCollisionStay(Collider* other)
	{
	}
	void ImpBomb::OnCollisionExit(Collider* other)
	{
	}
	void ImpBomb::attack()
	{
		Transform* tr = GetComponent<Transform>();
		object::Instantiate<Bomb>(tr->Pos() , eLayerType::Throws);
	}
	void ImpBomb::afterAction()
	{
		if(_Dir==eDir::R)
			_Animator->Play(L"Imp_Bomb_Idle_Right", true);
		else
			_Animator->Play(L"Imp_Bomb_Idle_Left", true);
	}
}