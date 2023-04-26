#include "MnNpcMelee.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnTime.h"
namespace Mn
{
	NpcMelee::NpcMelee()
		: GameObject()
		, _Collider(nullptr)
		, _Timer(0)
	{
	}
	NpcMelee::~NpcMelee()
	{
	}
	void NpcMelee::Initialize()
	{
		SetName(L"NpcMeleeAttack");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(30 * 3, 35 * 3));
		GameObject::Initialize();
	}
	void NpcMelee::Update()
	{
		_Timer += Time::DeltaTime();
		if (_Timer >= 0.3)
			this->State(eState::Death);
		GameObject::Update();
	}
	void NpcMelee::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void NpcMelee::Release()
	{
		GameObject::Release();
	}
}