#include "MnPortal.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnSceneManager.h"
#include "MnTransform.h"
#include "MnPlayScene.h"

namespace Mn
{
	Portal::Portal()
		:_Collider(nullptr)
	{
	}
	Portal::~Portal()
	{
	}
	void Portal::Initialize()
	{
		GameObject::SetName(L"Portal");
		
		Transform* tr = GetComponent<Transform>();
		Vector2 _Pos = Vector2(1200.0f, 500.0f);
		tr->Pos(_Pos);
		
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(20.0f, 60.0f));
		_Collider->Center(Vector2(-10.0f, -60.0f));

		GameObject::Initialize();
	}
	void Portal::Update()
	{
		GameObject::Update();
	}
	void Portal::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Portal::Release()
	{
	}
	void Portal::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"Player")
			PlayScene::ChangeScene(true);
	}
	void Portal::OnCollisionStay(Collider* other)
	{
	}
	void Portal::OnCollisionExit(Collider* other)
	{
	}
}