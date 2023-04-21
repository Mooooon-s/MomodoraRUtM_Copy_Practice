#include "MnFireFlame.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnRigidbody.h"
#include "MnTransform.h"
#include "MnCollider.h"
#include "MnCamera.h"
#include "MnTime.h"
namespace Mn
{
	FireFlame::FireFlame()
		:GameObject()
		, _Rigidbody(nullptr)
		, _Image(nullptr)
		, _Map(nullptr)
		, _Timer(0.0f)
		, _JumpForce(500.0f)
		, _Count(0)
	{
	}
	FireFlame::~FireFlame()
	{
	}
	void FireFlame::Initialize()
	{
		SetName(L"Throws");
		_Image = Resources::Load<Image>(L"FireFlame", L"..\\Resources\\FireBall_.bmp");
		_Map = Resources::Load<Image>(L"Arsonist_Map", L"..\\Resources\\Stage2_3.bmp");
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(1.0f);
		_Rigidbody->SetGround(false);
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(_Image->Width() * 2, _Image->Height() * 2));
		GameObject::Initialize();
	}
	void FireFlame::Update()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		pos.x += _Image->Width()*2 / 2.0f;
		pos.y += _Image->Height() * 2;
		COLORREF color = _Map->GetPixel(pos.x, pos.y);
		if(color == RGB(255,0,255))
		{
			_Rigidbody->SetGround(true);
			Vector2 newPos = Tr->Pos();
			newPos.y -= 1;
			Tr->Pos(newPos);
		}

		_Timer += Time::DeltaTime();
		if (_Timer >= 4.0)
			this->State(eState::Death);

		if (_Rigidbody->GetGround() == false)
		{
			if (fabs(_Rigidbody->Velocity().y) == 0)
			{
				Vector2 velocity = _Rigidbody->Velocity();
				velocity.y -= _JumpForce;
				_Rigidbody->Velocity(velocity);
			}
			if (fabs(_Rigidbody->Velocity().x) <= 100.0f)
				_Rigidbody->AddForce(_Dir * 10.0f);
		}
		else
		{
			if (_Count <= 3)
			{
				Vector2 velocity = _Rigidbody->Velocity();
				if(_JumpForce>=0)
					_JumpForce -= 100.0f;
				velocity.y -=_JumpForce;
				_Rigidbody->Velocity(velocity);
				_Rigidbody->SetGround(false);
				_Count++;
			}
		}
		GameObject::Update();
	}
	void FireFlame::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		pos = Camera::ComputePos(pos);
		TransparentBlt(hdc, pos.x, pos.y, _Image->Width()*2, _Image->Height()*2, _Image->Hdc(), 0, 0, _Image->Width(), _Image->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void FireFlame::Release()
	{
		GameObject::Release();
	}
	void FireFlame::OnCollisionEnter(Collider* other)
	{
	}
}