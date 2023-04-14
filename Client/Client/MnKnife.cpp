#include "MnKnife.h"
#include "MnResources.h"
#include "MnTime.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnAnimator.h"
#include "MnCollider.h"
namespace Mn
{
	Knife::Knife()
		: GameObject()
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Hit(false)
		, _Dir(eDir::R)
	{
	}
	Knife::~Knife()
	{
	}
	void Knife::Initialize()
	{
		SetName(L"Throws");
		_Image = Resources::Load<Image>(L"Throws_Knife", L"..\\Resources\\Imp_Knife.bmp");
		Vector2 offset = Vector2((_Image->Width()/2.0f*-1.0f)+1, -2.0f);
		
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(12*3,6*3));
		_Collider->Center(offset*3);

		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Throws_Knife_Left", _Image, Vector2::Zero, 1, 2, 1, Vector2(0,8*3) , 0.08);
		_Animator->CreateAnimation(L"Throws_Knife_Right", _Image, Vector2(0, 16), 1, 2, 1, Vector2(0, 8 * 3), 0.08);

		_Animator->Play(L"Throws_Knife_Left", false);
		GameObject::Initialize();
	}
	void Knife::Update()
	{
		if (_Hit == false)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			if (_Dir == eDir::L)
				pos.x -= 500.0f * Time::DeltaTime();
			else
				pos.x += 500.0f * Time::DeltaTime();
			tr->Pos(pos);
		}
		else
		{
			this->State(eState::Death);
		}
		GameObject::Update();
	}
	void Knife::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Knife::Release()
	{
		GameObject::Release();
	}
	void Knife::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"MeleeAttack")
		{
			_Hit = true;
		}
	}
	void Knife::OnCollisionStay(Collider* other)
	{
	}
	void Knife::OnCollisionExit(Collider* other)
	{
	}
	void Knife::Hit()
	{
		_Hit = true;
	}

	void Knife::DirR()
	{
		_Dir = eDir::R;
		_Animator->Play(L"Throws_Knife_Right", false);
	}

	void Knife::DirL()
	{
		_Dir = eDir::L;
		_Animator->Play(L"Throws_Knife_Left", false);
	}
}
