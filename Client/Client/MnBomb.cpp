#include "MnBomb.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnAnimator.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnRigidbody.h"
#include "MnGround.h"
#include "MnSceneManager.h"
#include "MnCamera.h"
namespace Mn
{
	Bomb::Bomb()
		: GameObject()
		, _Collider(nullptr)
		, _Image(nullptr)
		, _Animator(nullptr)
		, _Rigidbody(nullptr)
		, _GroundImage(nullptr)
		, _Time(0.0f)
		, _Dir(0)
		, _blowUp(false)
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
		_Image = Resources::Load<Image>(L"Smoke_", L"..\\Resources\\Smoke.bmp");
		_Animator->CreateAnimation(L"Smoke", _Image, Vector2::Zero, 7, 1, 7, Vector2::Zero, 0.08);
		_Animator->GetCompleteEvent(L"Smoke") = std::bind(&Bomb::afterBlowUp, this);
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(0.5f);
		_Rigidbody->SetGround(false);
		Vector2 velocity = _Rigidbody->Velocity();
		velocity.y -= 500.0f;
		_Rigidbody->Velocity(velocity);
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(16*2, 16*2));
		_Collider->Center(Vector2(-8*2, -16*2));
		Transform* tr = GetComponent<Transform>();
		_Pos = tr->Pos();
		_Animator->Play(L"Bomb_Right", false);
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> ground = scene->GetGameObject(eLayerType::Ground);
		for (auto v : ground)
		{
			if (dynamic_cast<Ground*>(v))
				_GroundImage = dynamic_cast<Ground*>(v)->Map();
		}
	}
	void Bomb::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 underpos = tr->Pos();
		Vector2 leftpos = Vector2(underpos.x - 8 * 2,underpos.y);
		Vector2 rightpos = Vector2(underpos.x + 8 * 2, underpos.y);

		COLORREF Footcolor = _GroundImage->GetPixel(underpos.x, underpos.y);
		COLORREF leftColor = _GroundImage->GetPixel(leftpos.x, leftpos.y);
		COLORREF rightColor = _GroundImage->GetPixel(rightpos.x, rightpos.y);

		if (Footcolor != RGB(0, 0, 0) )
		{
			_blowUp = true;
			_Rigidbody->SetGround(true);
			_Animator->Play(L"Smoke", true);
		}


		if (_Rigidbody->GetGround() == false)
		{
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
		}


		GameObject::Update();
	}
	void Bomb::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 underpos = tr->Pos();
		Vector2 leftpos = Vector2(underpos.x - 8 * 2, underpos.y);
		Vector2 rightpos = Vector2(underpos.x + 8 * 2, underpos.y);
		underpos = Camera::ComputePos(underpos);
		leftpos = Camera::ComputePos(leftpos);
		rightpos = Camera::ComputePos(rightpos);
		Rectangle(hdc, underpos.x, underpos.y, underpos.x + 2, underpos.y + 2);
		Rectangle(hdc, leftpos.x, leftpos.y, leftpos.x + 5, leftpos.y + 5);
		Rectangle(hdc, rightpos.x, rightpos.y, rightpos.x + 10, rightpos.y + 10);


		GameObject::Render(hdc);
	}
	void Bomb::Release()
	{
		GameObject::Release();
	}
	void Bomb::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"Player" && _blowUp==false)
		{
			_blowUp = true;
			_Rigidbody->SetGround(true);
			_Animator->Play(L"Smoke", false);
		}
	}
	void Bomb::OnCollisionStay(Collider* other)
	{
	}
	void Bomb::OnCollisionExit(Collider* other)
	{
	}
	void Bomb::afterBlowUp()
	{
		this->State(eState::Death);
	}
}