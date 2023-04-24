#include "MnMagnolia.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnRigidbody.h"

#include "MnResources.h"
#include "MnTime.h"
#include "MnMagArrow.h"
#include "MnObject.h"
namespace Mn
{
	Magnolia::Magnolia()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _State(eMagnoliaState::Idle)
		, _Dir(eDir::R)
		, _Timer(0.0f)
		, _ArrowTimer(0.0f)

	{
		Transform* Tr = GetComponent<Transform>();
		Tr->Pos(Vector2(157,900));
	}
	Magnolia::~Magnolia()
	{
	}
	void Magnolia::Initialize()
	{
		GameObject::Initialize();
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(true);

		_Image = Resources::Load<Image>(L"Magnolia_Arrow", L"..\\Resources\\Magnolia_Arrow.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Magnolia_Arrow_Idle_Left", _Image, Vector2::Zero, 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Idle_Right", _Image, Vector2(0,48), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Attack_Left", _Image, Vector2(0,48*2), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Attack_Right", _Image, Vector2(0,48*3), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Land_Left", _Image, Vector2(0, 48 * 4), 6, 6, 6, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Arrow_Land_Right", _Image, Vector2(0, 48 * 5), 6, 6, 6, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Magnolia_Knife", L"..\\Resources\\Magnolia_knife.bmp");
		_Animator->CreateAnimation(L"Magnolia_Knife_Idle_Left", _Image, Vector2::Zero, 4, 4, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Idle_Right", _Image, Vector2(0, 48), 4, 4, 4, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Hurt_Left", _Image, Vector2(0, 48 * 2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_hurt_Right", _Image, Vector2(0, 48 * 3), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Death_Left", _Image, Vector2(48, 48 * 2), 4, 4, 1, Vector2::Zero, 0.08);
		_Animator->CreateAnimation(L"Magnolia_Knife_Death_Right", _Image, Vector2(48, 48 * 2), 4, 4, 1, Vector2::Zero, 0.08);

		_Animator->FindAnimation(L"Magnolia_Arrow_Attack_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Magnolia::afterPattarn2, this);
		_Animator->FindAnimation(L"Magnolia_Arrow_Attack_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Magnolia::afterPattarn2, this);

		_Animator->FindAnimation(L"Magnolia_Arrow_Land_Right")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Magnolia::afterPattarn, this);
		_Animator->FindAnimation(L"Magnolia_Arrow_Land_Left")->GetSprite(4)._Events._FrameEvent._Event = std::bind(&Magnolia::afterPattarn, this);

		_Animator->Play(L"Magnolia_Arrow_Idle_Right", true);
	}
	void Magnolia::Update()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (pos.x <= 157 && pos.y >= 340)
		{
			showUp();
		}
		switch (_State)
		{
		case eMagnoliaState::Idle:
			idle();
			break;
		case eMagnoliaState::pattarn1:
			pattarn1();
			break;
		case eMagnoliaState::pattarn2:
			pattarn2();
			break;
		case eMagnoliaState::ShowUp:
			showUp();
			break;
		case eMagnoliaState::DisAppear:
			disAppear();
			break;
		default:
			break;
		}
		GameObject::Update();
	}
	void Magnolia::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Magnolia::Release()
	{
		GameObject::Release();
	}
	void Magnolia::OnCollisionEnter(Collider* other)
	{
	}
	void Magnolia::OnCollisionStay(Collider* other)
	{
	}
	void Magnolia::OnCollisionExit(Collider* other)
	{
	}
	void Magnolia::animationCtrl()
	{
		switch (_State)
		{
		case eMagnoliaState::Idle:
			if (_Dir == eDir::R)
				_Animator->Play(L"Magnolia_Arrow_Idle_Right", true);
			else
				_Animator->Play(L"Magnolia_Arrow_Idle_Left", true);
			break;
		case eMagnoliaState::pattarn1:
			_Animator->Play(L"Magnolia_Arrow_Attack_Left", false);
			break;
		case eMagnoliaState::pattarn2:
			_Animator->Play(L"Magnolia_Arrow_Attack_Right", false);
			break;
		case eMagnoliaState::ShowUp:
			if (_Dir == eDir::R)
				_Animator->Play(L"Magnolia_Arrow_Idle_Right", true);
			else
				_Animator->Play(L"Magnolia_Arrow_Idle_Left", true);
			break;
		case eMagnoliaState::DisAppear:
			if (_Dir == eDir::R)
				_Animator->Play(L"Magnolia_Arrow_Idle_Right", true);
			else
				_Animator->Play(L"Magnolia_Arrow_Idle_Left", true);
			break;
		case eMagnoliaState::Land:
			if (_Dir == eDir::R)
				_Animator->Play(L"Magnolia_Arrow_Land_Right", false);
			else
				_Animator->Play(L"Magnolia_Arrow_Land_Left", false);
			break;
		default:
			break;
		}
	}
	void Magnolia::pattarn1()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Jump == true)
		{

			if (pos.x >= 157)
			{
				pos.x -= 400 * Time::DeltaTime();
				Tr->Pos(pos);
			}
			else
			{
				_Jump = false;
				_State = eMagnoliaState::Land;
				animationCtrl();
			}
			_ArrowTimer += Time::DeltaTime();
			if (_ArrowTimer >= 0.2)
			{
				MagArrow* mag = object::Instantiate<MagArrow>(pos,eLayerType::Throws);
				mag->BlowUp(false);
				_ArrowTimer = 0;
			}
		}
	}
	void Magnolia::pattarn2()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_Jump == true)
		{

			if (pos.x <= 480)
			{
				pos.x += 400 * Time::DeltaTime();
				Tr->Pos(pos);
			}
			else
			{
				_Jump = false;
				_State = eMagnoliaState::DisAppear;
			}

		}
	}
	void Magnolia::showUp()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (pos.y >= 340.0f)
		{
			pos.y -= 1500.0f * Time::DeltaTime();
			Tr->Pos(pos);
		}
		else
		{
			_Timer = 0;
			afterPattarn();
		}
	}
	void Magnolia::disAppear()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		MagArrow* mag = object::Instantiate<MagArrow>(pos, eLayerType::Throws);
		mag->BlowUp(true);
		pos.x = 877.0f;
		pos.y = 900.0f;
		Tr->Pos(pos);
		_Timer += Time::DeltaTime();
		if (_Timer >= 4)
		{
			_State = eMagnoliaState::ShowUp;
		}
	}
	void Magnolia::afterPattarn()
	{
		if (_Dir == eDir::R)
			_Dir = eDir::L;
		else
			_Dir = eDir::R;
		_State = eMagnoliaState::Idle;
		animationCtrl();
	}
	void Magnolia::afterPattarn2()
	{
		_Jump = true;
	}
	void Magnolia::idle()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (pos.x == 877.0f && pos.y == 900.0f)
			showUp();
		_Timer += Time::DeltaTime();
		if (_Dir == eDir::R && _Timer >=3)
		{
			_Timer = 0;
			_State = eMagnoliaState::pattarn2;
			animationCtrl();
		}
		else if(_Dir == eDir::L && _Timer >=5)
		{
			_Timer = 0;
			_State = eMagnoliaState::pattarn1;
			animationCtrl();
		}
	}
}