#include "MnMapTrriger.h"
#include "MnCollider.h"
#include "MnComponent.h"
#include "MnTransform.h"
namespace Mn
{
	MapTrriger::MapTrriger()
		: GameObject()
		, _Collider(nullptr)
		, _Trriger(false)
	{
		Transform* Tr = GetComponent<Transform>();
		Tr->Pos(Vector2(-200, -200));
	}
	MapTrriger::~MapTrriger()
	{
	}
	void MapTrriger::Initialize()
	{
		SetName(L"MapTrriger");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(32*3,32*3));
		_Collider->Center(Vector2(-16 * 3, 32 * 3));
		GameObject::Initialize();
	}
	void MapTrriger::Update()
	{
		GameObject::Update();
	}
	void MapTrriger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MapTrriger::Release()
	{
		GameObject::Release();
	}
	void MapTrriger::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"Player")
		{
			_Trriger = true;
		}
	}
}