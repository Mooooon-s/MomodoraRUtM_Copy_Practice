#include "MnStaff.h"
#include "MnAnimator.h"
#include "MnImage.h"
#include "MnResources.h"
#include "MnCollider.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnCatPeasant.h"
#include "MnSound.h"
namespace Mn
{
	Staff::Staff()
		: GameObject()
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Image(nullptr)
		, _DirVec(Vector2::Zero)
		, _GetBack(0.0f)
		, _Return(false)
		, _Count(0)
		, _StaffRotatSound(nullptr)
		, _Timer(0.0f)
	{
		Transform* Tr = GetComponent<Transform>();
		Tr->Pos(Vector2(-200,-200));
	}
	Staff::~Staff()
	{
	}
	void Staff::Initialize()
	{
		SetName(L"Throws");
		_Image = Resources::Load<Image>(L"Staff", L"..\\Resources\\Staff.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Staff_Right", _Image, Vector2::Zero, 8, 2, 8, Vector2::Zero, 0.04);
		_Animator->CreateAnimation(L"Staff_Left", _Image, Vector2(0,64), 8, 2, 8, Vector2::Zero, 0.04);

		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(64 * 3, 64 * 3));
		_Collider->Center(Vector2(-32 * 3, -64 * 3));

		_StaffRotatSound = Resources::Load<Sound>(L"RotateSound", L"..\\Resources\\Sound\\StaffRotation.wav");

		GameObject::Initialize();
	}
	void Staff::Update()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_DirVec.x <= 0)
			_Animator->Play(L"Staff_Left", true);
		else
			_Animator->Play(L"Staff_Right", true);
		_GetBack += Time::DeltaTime();
		if (_GetBack >= 2)
		{
			pos += (_DirVec*-1) * 1000.0f * Time::DeltaTime();
			if (_GetBack >= 6)
				this->State(eState::Death);
		}
		else
		{
			pos += (_DirVec) * 1000.0f * Time::DeltaTime();
		}

		_Timer += Time::DeltaTime();
		if (_Timer >= 0.13)
		{
			_StaffRotatSound->Stop(true);
			_StaffRotatSound->Play(false);
			_StaffRotatSound->SetVolume(25.0f);
			_Timer = 0;
		}

		Tr->Pos(pos);
		if (_Count >= 2)
			_Return = true;
		GameObject::Update();
	}
	void Staff::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Staff::Release()
	{
		GameObject::Release();
	}
	void Staff::OnCollisionEnter(Collider* other)
	{
		if (dynamic_cast<CatPeasant*>(other->Owner()))
			_Count++;
	}
}