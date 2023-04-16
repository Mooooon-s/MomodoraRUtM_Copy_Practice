#include "MnMonMeleeAttack.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnTime.h"
namespace Mn
{
	MonMeleeAttack::MonMeleeAttack()
		: GameObject()
		, _Collider(nullptr)
		, _Time(0.0f)
	{
	}
	MonMeleeAttack::~MonMeleeAttack()
	{
	}
	void MonMeleeAttack::Initialize()
	{
		SetName(L"Throws");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(20*3, 20*3));
	}
	void MonMeleeAttack::Update()
	{
		_Time += Time::DeltaTime();
		if (_Time >= 0.4)
			Done();
		GameObject::Update();
	}
	void MonMeleeAttack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MonMeleeAttack::Release()
	{
		GameObject::Release();
	}
	void MonMeleeAttack::OnCollisionEnter(Collider* other)
	{
	}
	void MonMeleeAttack::OnCollisionStay(Collider* other)
	{
	}
	void MonMeleeAttack::OnCollisionExit(Collider* other)
	{
	}
	void MonMeleeAttack::Done()
	{
		this->State(eState::Death);
	}
}