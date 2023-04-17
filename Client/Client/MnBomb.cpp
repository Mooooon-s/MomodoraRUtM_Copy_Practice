#include "MnBomb.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnTime.h"

namespace Mn
{
	Bomb::Bomb()
		: GameObject()
		, _Collider(nullptr)
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Time(0.0f)
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
		Transform* tr = GetComponent<Transform>();
		_Pos = tr->Pos();
		_Animator->Play(L"Bomb_Left", false);
	}
	void Bomb::Update()
	{
		if (_Pos.x == 0 && _Pos.y == 0)
		{
			Transform* tr = GetComponent<Transform>();
			_Pos = tr->Pos();
		}
		float speed = 100.0f;
		int radian = 45 * PI / 180;
		float gravity = 9.81;
		_Time += Time::DeltaTime();
		float x =speed * cos(radian) * _Time;
		float y =speed * sin(radian) * _Time - (0.5f * gravity * (_Time * _Time));
		Transform* tr = GetComponent<Transform>();
		tr->Pos(_Pos + Vector2(x,y*-1));
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