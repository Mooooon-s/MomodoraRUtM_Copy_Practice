#include "MnCatPeasant.h"
#include "MnComponent.h"
#include "MnImage.h"
#include "MnAnimator.h"
#include "MnResources.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnSceneManager.h"
#include "MnKaho.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnObject.h"
#include "MnStaff.h"
#include "MnHitEffect.h"
namespace Mn
{
	CatPeasant::CatPeasant()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _HaveStaff(true)
		, _Staff(nullptr)
		, _MonState(eMonstate::Idle)
		, _Dir(eDir::R)
		, _Kaho(nullptr)
		, _Ready(0.0f)
		, _Hp(8)
	{
		Transform* Tr = GetComponent<Transform>();
		Tr->Pos(Vector2(-200,-200));
	}
	CatPeasant::~CatPeasant()
	{
	}
	void CatPeasant::Initialize()
	{
		SetName(L"Enemy");

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetGround(true);
		_Rigidbody->SetMass(1.0f);


		_Image = Resources::Load<Image>(L"Cat_Peasant", L"..\\Resources\\Cat_Peasant.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Cat_Peasant_Idle_Staff_Right", _Image, Vector2::Zero, 9, 10, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Idle_Staff_Left", _Image, Vector2(0,64), 9, 10, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Hurt_Staff_Right", _Image, Vector2(64*5,0), 9, 10, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Hurt_Staff_Left", _Image, Vector2(64*5,64), 9, 10, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Throw_Staff_Right", _Image, Vector2(0,64*2), 9, 10, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Throw_Staff_Left", _Image, Vector2(0,64*3), 9, 10, 9, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Death_Staff_Right", _Image, Vector2(0,64*4), 9, 10, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Death_Staff_Left", _Image, Vector2(0,64*5), 9, 10, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Idle_Right", _Image, Vector2(0,64*6), 9, 10, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Idle_Left", _Image, Vector2(0,64*7), 9, 10, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Hurt_Right", _Image, Vector2(64*5,64*6), 9, 10, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Hurt_Left", _Image, Vector2(64*5,64*7), 9, 10, 5, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Death_Right", _Image, Vector2(0,64*8), 9, 10, 8, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Death_Left", _Image, Vector2(0,64*9), 9, 10, 8, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Cat_Peasant_Catch_Staff", L"..\\Resources\\Get_Staff.bmp");
		_Animator->CreateAnimation(L"Cat_Peasant_Catch_Right", _Image, Vector2::Zero, 5, 2, 5, Vector2(0, 16 * 3), 0.08);
		_Animator->CreateAnimation(L"Cat_Peasant_Catch_Left", _Image, Vector2(0,96), 5, 2, 5, Vector2(0, 16 * 3), 0.08);

		_Animator->GetCompleteEvent(L"Cat_Peasant_Throw_Staff_Right") = std::bind(&CatPeasant::staff, this);
		_Animator->GetCompleteEvent(L"Cat_Peasant_Throw_Staff_Left") = std::bind(&CatPeasant::staff, this);
		_Animator->GetCompleteEvent(L"Cat_Peasant_Catch_Right") = std::bind(&CatPeasant::staff, this);
		_Animator->GetCompleteEvent(L"Cat_Peasant_Catch_Left") = std::bind(&CatPeasant::staff, this);

		_Animator->FindAnimation(L"Cat_Peasant_Throw_Staff_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&CatPeasant::throwStaff, this);
		_Animator->FindAnimation(L"Cat_Peasant_Throw_Staff_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&CatPeasant::throwStaff, this);

		_Animator->FindAnimation(L"Cat_Peasant_Death_Staff_Right")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&CatPeasant::death, this);
		_Animator->FindAnimation(L"Cat_Peasant_Death_Staff_Left")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&CatPeasant::death, this);
		_Animator->FindAnimation(L"Cat_Peasant_Death_Right")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&CatPeasant::death, this);
		_Animator->FindAnimation(L"Cat_Peasant_Death_Left")->GetSprite(7)._Events._FrameEvent._Event = std::bind(&CatPeasant::death, this);

		_Animator->Play(L"Cat_Peasant_Idle_Staff_Right", true);
		
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(24.0f * 3, 38.0f * 3));
		_Collider->Center(Vector2(-12.0f * 3, ((-40.0f*3)-(_Image->Height()/10))));
		
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
	void CatPeasant::Update()
	{
		if(_HaveStaff)
		{
			switch (_MonState)
			{
			case eMonstate::Idle:
				idle();
				break;
			case eMonstate::Attack:
				break;
			case eMonstate::Hurt:
				break;
			case eMonstate::Death:
				break;
			default:
				break;
			}
		}
		else
		{
			switch (_MonState)
			{
			case eMonstate::Idle:
				idle();
				break;
			case eMonstate::Catch:
				break;
			case eMonstate::Hurt:
				break;
			case eMonstate::Death:
				break;
			default:
				break;
			}
		}

		if (_Hp <= 0 && _MonState != eMonstate::Death )
		{
			_MonState = eMonstate::Death;
			animationCtrl();
		}


		GameObject::Update();
	}
	void CatPeasant::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CatPeasant::Release()
	{
		GameObject::Release();
	}
	void CatPeasant::OnCollisionEnter(Collider* other)
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
	void CatPeasant::OnCollisionStay(Collider* other)
	{
	}
	void CatPeasant::OnCollisionExit(Collider* other)
	{
	}
	void CatPeasant::animationCtrl()
	{
		if (_HaveStaff)
		{
			switch (_MonState)
			{
			case eMonstate::Idle:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Idle_Staff_Right", true);
				else
					_Animator->Play(L"Cat_Peasant_Idle_Staff_Left", true);
				break;
			case eMonstate::Attack:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Throw_Staff_Right", false);
				else
					_Animator->Play(L"Cat_Peasant_Throw_Staff_Left", false);
				break;
			case eMonstate::Hurt:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Hurt_Staff_Right", true);
				else
					_Animator->Play(L"Cat_Peasant_Hurt_Staff_Left", true);
				break;
			case eMonstate::Death:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Death_Staff_Right", false);
				else
					_Animator->Play(L"Cat_Peasant_Death_Staff_Left", false);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (_MonState)
			{
			case eMonstate::Idle:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Idle_Right", true);
				else
					_Animator->Play(L"Cat_Peasant_Idle_Left", true);
				break;
			case eMonstate::Catch:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Catch_Right", false);
				else
					_Animator->Play(L"Cat_Peasant_Catch_Left", false);
				break;
			case eMonstate::Hurt:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Hurt_Right", true);
				else
					_Animator->Play(L"Cat_Peasant_Hurt_Left", true);
				break;
			case eMonstate::Death:
				if (_Dir == eDir::R)
					_Animator->Play(L"Cat_Peasant_Death_Right", false);
				else
					_Animator->Play(L"Cat_Peasant_Death_Left", false);
				break;
			default:
				break;
			}
		}
	}
	void CatPeasant::idle()
	{
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		Vector2 playerPos = playerTr->Pos();
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Vector2 dir = playerPos - pos;
		if (dir.x <= 0)
		{
			_Dir = eDir::L;
			animationCtrl();
		}
		else
		{
			_Dir = eDir::R;
			animationCtrl();
		}
		if (_HaveStaff)
		{
			_Ready += Time::DeltaTime();
			if (_Ready >= 3)
			{
				_Ready = 0;
				_MonState = eMonstate::Attack;
				animationCtrl();
			}
		}
		if (_Staff!=nullptr && _Staff->Done())
		{
			_Staff->State(eState::Death);
			_Staff = nullptr;
			_MonState = eMonstate::Catch;
			animationCtrl();
		}
	}
	void CatPeasant::staff()
	{
		if(_HaveStaff==true)
			_HaveStaff = false;
		else if (_HaveStaff==false)
			_HaveStaff = true;
		_MonState = eMonstate::Idle;
		animationCtrl();
	}
	void CatPeasant::death()
	{
		this->State(eState::Death);
	}
	void CatPeasant::throwStaff()
	{
		Transform* playerTr = _Kaho->GetComponent<Transform>();
		Vector2 playerPos = playerTr->Pos();
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Vector2 dir = playerPos - pos;
		pos.y -= _Collider->Size().y/2.0f;
		_Staff = object::Instantiate<Staff>(pos,eLayerType::Throws);
		_Staff->DirVector(dir.Normalize());
	}
}