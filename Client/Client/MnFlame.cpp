#include "MnFlame.h"
#include "MnTime.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnTransform.h"
#include "MnCamera.h"
#include "MnSound.h"
namespace Mn
{
	Flame::Flame()
		: GameObject()
		, _Flame(nullptr)
		, _Timer(0.0f)
		, _Collider(nullptr)
	{
	}
	Flame::~Flame()
	{
	}
	void Flame::Initialize()
	{
		SetName(L"Throws");
		_Flame = Resources::Load<Image>(L"Flame", L"..\\Resources\\Flame.bmp");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(_Flame->Width()*3, _Flame->Height()*3));
		_Collider->Center(Vector2(0.0f,_Flame->Height() * 3.0f*-1));
		Sound* explosion = Resources::Load<Sound>(L"Explosion",L"..\\Resources\\Sound\\Explosion.wav");
		explosion->Play(false);
		GameObject::Initialize();
	}
	void Flame::Update()
	{
		_Timer += Time::DeltaTime();
		if (_Timer >= 1.5f)
			this->State(eState::Death);
		GameObject::Update();
	}
	void Flame::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos =Tr->Pos();
		pos = Camera::ComputePos(pos);
		TransparentBlt(hdc, pos.x, 0, _Flame->Width() * 3, _Flame->Height() * 3, _Flame->Hdc(), 0, 0, _Flame->Width(), _Flame->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void Flame::Release()
	{
		GameObject::Release();
	}
	void Flame::OnCollisionEnter(Collider* other)
	{
	}
	void Flame::OnCollisionStay(Collider* other)
	{
	}
	void Flame::OnCollisionExit(Collider* other)
	{
	}
}