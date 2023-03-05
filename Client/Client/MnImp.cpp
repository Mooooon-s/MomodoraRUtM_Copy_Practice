#include "MnImp.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnSceneManager.h"
#include "MnTime.h"

namespace Mn
{
	Imp::Imp()
		:_animator(nullptr)
		,_Pos(Vector2::Zero)
		,_Status(eMonStatus::Move)
		,_Time(0)
	{
	}
	Imp::~Imp()
	{
	}
	void Imp::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos = Vector2(700.0f, 400.0f);
		tr->Pos(_Pos);
		Image* _Image = Resources::Load<Image>(L"Imp", L"..\\Resources\\Imp.bmp");
		_animator = AddComponent<Animator>();
		
		_animator->CreateAnimation(L"Imp_Idle_Right", _Image, Vector2::Zero, 8, 5, 1, Vector2::Zero, 0.1f);
		_animator->CreateAnimation(L"Imp_Idle_Left", _Image, Vector2(32,0), 8, 5, 1, Vector2::Zero, 0.1f);
		_animator->CreateAnimation(L"Imp_Walk_Right", _Image, Vector2(0, 32), 8, 5, 5, Vector2::Zero, 0.1f);
		_animator->CreateAnimation(L"Imp_Walk_Left", _Image, Vector2(0, 32*2), 8, 5, 5, Vector2::Zero, 0.1f);
		_animator->CreateAnimation(L"Imp_Attack_Right", _Image, Vector2(0, 32*3), 8, 5, 8, Vector2::Zero, 0.1f);
		_animator->CreateAnimation(L"Imp_Attack_Left", _Image, Vector2(0, 32 * 4), 8, 5, 8, Vector2::Zero, 0.1f);

		_animator->Play(L"Imp_Idle_Right", true);

		GameObject::Initialize();
	}
	void Imp::Update()
	{
		_Time += Time::DeltaTime();

		if (_Time >= 3.0f)
		{
			_Status = think();
			switch (_Status)
			{
			case Mn::Imp::eMonStatus::Move:
				move();
				break;
			case Mn::Imp::eMonStatus::Attack:
				attack();
				break;
			case Mn::Imp::eMonStatus::Defence:
				defence();
				break;
			default:
				break;
			}
			_Time = 0;
		}
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
	void Imp::move()
	{
		_animator->Play(L"Imp_Walk_Right", true);
	}
	void Imp::attack()
	{
		_animator->Play(L"Imp_Attack_Right", false);
	}
	void Imp::defence()
	{
		_animator->Play(L"Imp_Idle_Right", false);
	}
	Imp::eMonStatus Imp::think()
	{
		int behave = 0;
		behave = rand() % 3;
		return eMonStatus(behave);
	}
}