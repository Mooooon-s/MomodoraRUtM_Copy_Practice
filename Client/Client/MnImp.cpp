#include "MnImp.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnKaho.h"
#include "MnPlayScene.h"
#include "MnObject.h"
#include "MnKnife.h"

namespace Mn
{
	Imp::Imp()
		: _Animator(nullptr)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _Pos(Vector2::Zero)
		, _Status(eMonStatus::Move)
		, _HurtTime(0)
		, _Hp(3)
		, _MoveCount(0)
		, _Dir(eDir::R)
	{
	}
	Imp::~Imp()
	{
	}
	void Imp::Initialize()
	{
		GameObject::SetName(L"Enemy");
		Transform* tr = GetComponent<Transform>();
		_Pos = Vector2(700.0f, 400.0f);
		tr->Pos(_Pos);

		_Collider = AddComponent<Collider>();
		_Collider->Center(Vector2(-10*3,-20*3));
		_Collider->Size(Vector2(20*3, 20*3));

		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0);
		_Rigidbody->SetGround(false);

		_Image = Resources::Load<Image>(L"Imp", L"..\\Resources\\Imp.bmp");
		_Animator = AddComponent<Animator>();
		
		_Animator->CreateAnimation(L"Imp_Idle_Right", _Image, Vector2::Zero, 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Idle_Left", _Image, Vector2(32,0), 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Hurt_Right", _Image, Vector2(32*2, 0), 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Hurt_Left", _Image, Vector2(32*3, 0), 8, 5, 1, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Walk_Right", _Image, Vector2(0, 32), 8, 5, 5, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Walk_Left", _Image, Vector2(0, 32*2), 8, 5, 5, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Attack_Right", _Image, Vector2(0, 32*3), 8, 5, 8, Vector2::Zero, 0.1f);
		_Animator->CreateAnimation(L"Imp_Attack_Left", _Image, Vector2(0, 32 * 4), 8, 5, 8, Vector2::Zero, 0.1f);
		_Animator->GetCompleteEvent(L"Imp_Attack_Right") = std::bind(&Imp::affterAttack, this);
		_Animator->GetCompleteEvent(L"Imp_Attack_Left") = std::bind(&Imp::affterAttack, this);
		_Animator->FindAnimation(L"Imp_Attack_Left")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&Imp::throwKnife, this);
		_Animator->FindAnimation(L"Imp_Attack_Right")->GetSprite(3)._Events._FrameEvent._Event = std::bind(&Imp::throwKnife, this);

		_Animator->Play(L"Imp_Idle_Right", true);
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> playerobj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerobj)
		{
			if (dynamic_cast<Kaho*>(v))
				_kaho = dynamic_cast<Kaho*>(v);
		}
		GameObject::Initialize();
	}
	void Imp::Update()
	{
		Vector2 playerPos = _kaho->CameraTarget<GameObject>()->GetComponent<Transform>()->Pos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		float distX = pos.x - playerPos.x;
		_Pos = tr->Pos();
		_ThinkTime += Time::DeltaTime();
		if (_ThinkTime >= 0.7f)
		{
			_Status = think();
			if (distX < 0)
				_Dir = eDir::R;
			else
				_Dir = eDir::L;
			animationCntrl();
			_ThinkTime = 0;
		}
		switch (_Status)
		{
		case eMonStatus::Move:
			move();
			break;
		case eMonStatus::Attack:
			attack();
			break;
		case eMonStatus::Defence:
			defence();
			break;
		case eMonStatus::Hurt:
			hurt();
			break;
		default:
			break;
		}
		tr->Pos(_Pos);
		if (_Hp <= 0)
			GameObject::State(eState::Death);
		GameObject::Update();
	}
	void Imp::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Imp::Release()
	{
		GameObject::Release();
	}
	void Imp::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"meleeAttack")
		{
			Vector2 dir = _Pos - _kaho->CameraTarget<GameObject>()->GetComponent<Transform>()->Pos();
			if ((_Dir == eDir::R && dir.x > 0) || (_Dir == eDir::L && dir.x < 0))
			{
				_Status = eMonStatus::Hurt;
				animationCntrl();
				_Hp -= 1.5f;
				_HurtTime = 0;
				_ThinkTime = 0;
			}
			else
			{
				_Status = eMonStatus::Defence;
				animationCntrl();
			}
		}

		if (other->Owner()->GetName() == L"Arrow")
		{
			Vector2 dir = _Pos - _kaho->CameraTarget<GameObject>()->GetComponent<Transform>()->Pos();
			if ((_Dir == eDir::R && dir.x > 0) || (_Dir == eDir::L && dir.x < 0))
			{
				_Status = eMonStatus::Hurt;
				animationCntrl();
				_Hp -= 1.0f;
				_HurtTime = 0;
				_ThinkTime = 0;
			}
			else
			{
				_Status = eMonStatus::Defence;
				animationCntrl();
			}
		}

	}
	void Imp::OnCollisionStay(Collider* other)
	{
	}
	void Imp::OnCollisionExit(Collider* other)
	{
	}
	void Imp::move()
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
		if (fabs(distX) >=150)
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
	}
	void Imp::attack()
	{
		//Throw knife
	}
	void Imp::defence()
	{

	}
	void Imp::hurt()
	{
		_HurtTime += Time::DeltaTime();
		if (_HurtTime >= 0.5)
		{
			_Status = eMonStatus::Defence;
			animationCntrl();
			_HurtTime = 0;
		}
	}
	void Imp::animationCntrl()
	{
		switch (_Status)
		{
		case eMonStatus::Move:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Walk_Right", true);
			else
				_Animator->Play(L"Imp_Walk_Left", true);
			break;
		case eMonStatus::Attack:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Attack_Right", false);
			else
				_Animator->Play(L"Imp_Attack_Left", false);
			break;
		case eMonStatus::Defence:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Idle_Right", false);
			else
				_Animator->Play(L"Imp_Idle_Left", false);
			break;
		case eMonStatus::Hurt:
			if (_Dir == eDir::R)
				_Animator->Play(L"Imp_Hurt_Right", false);
			else
				_Animator->Play(L"Imp_Hurt_Right", false);
			break;
		default:
			break;
		}
	}
	Imp::eMonStatus Imp::think()
	{
		if (_MoveCount > 3)
		{
			_MoveCount = 0;
			return eMonStatus::Attack;
		}
		else
		{
			_MoveCount++;
			return eMonStatus::Move;
		}
	}
	void Imp::affterAttack()
	{
		_Status = eMonStatus::Defence;
		animationCntrl();
	}
	void Imp::throwKnife()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		pos.y -= _Collider->Size().y / 2.0f;
		if (_Dir == eDir::R)
		{
			pos.x += (_Collider->Size().x / 2.0f);
			Knife* knife = object::Instantiate<Knife>(pos,eLayerType::Throws);
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