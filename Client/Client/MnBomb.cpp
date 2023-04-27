#include "MnBomb.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnRigidbody.h"

namespace Mn
{
	Bomb::Bomb()
		: GameObject()
		, _Collider(nullptr)
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _Time(0.0f)
		, _Dir(0)
	{
	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		_Image = Resources::Load<Image>(L"Throws_Bomb", L"..\\Resources\\Imp_Bomb.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Bomb_Left", _Image, Vector2::Zero, 1, 2, 1, Vector2::Zero, 0.08f);
		_Animator->CreateAnimation(L"Bomb_Right", _Image, Vector2(0,16), 1, 2, 1, Vector2::Zero, 0.08f);
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(0.5f);
		_Rigidbody->SetGround(false);
		Vector2 velocity = _Rigidbody->Velocity();
		velocity.y -= 500.0f;
		_Rigidbody->Velocity(velocity);

		Transform* tr = GetComponent<Transform>();
		_Pos = tr->Pos();
		_Animator->Play(L"Bomb_Right", false);
	}
	void Bomb::Update()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos = tr->Pos();
		if (_Dir == 0)
		{
			_Pos.x += 150 * Time::DeltaTime();
		}
		else 
		{
			_Pos.x -= 150 * Time::DeltaTime();
		}
		tr->Pos(_Pos);
		GameObject::Update();
	}
	void Bomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bomb::Release()
	{
		GameObject::Release();
	}
	void Bomb::OnCollisionEnter(Collider* other)
	{
	}
	void Bomb::OnCollisionStay(Collider* other)
	{
	}
	void Bomb::OnCollisionExit(Collider* other)
	{
	}
}