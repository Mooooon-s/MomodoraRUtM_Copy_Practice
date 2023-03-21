#include "MnGround.h"
#include "MnCollider.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"
#include "MnKaho.h"
#include "MnRigidbody.h"
#include "MnTransform.h"

namespace Mn
{
	Ground::Ground()
	{
	}
	Ground::~Ground()
	{
	}
	void Ground::Initialize()
	{
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(920.0f, 50.0f));
		GameObject::Initialize();
	}
	void Ground::Update()
	{
		GameObject::Update();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ground::Release()
	{
	}
	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* obj = dynamic_cast<GameObject*>(other->Owner());
		if (obj == nullptr)
			return;

		Rigidbody* rb = obj->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* objColl = obj->GetComponent<Collider>();
		Vector2 objPos = objColl->Pos();

		Collider* groundColl = this->GetComponent<Collider>();
		Vector2 groundPos = groundColl->Pos();

		float fLen = fabs(objPos.y - groundPos.y);
		float fSize = (objColl->Size().y / 2.0f + groundColl->Size().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* objTr = obj->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 objPos = objTr->Pos();
			Vector2 grPos = grTr->Pos();

			objPos -= (fSize - fLen) - 1.0f;
			objTr->Pos(objPos);
		}

	}
	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
		GameObject* obj = dynamic_cast<GameObject*>(other->Owner());
		if (obj == nullptr)
			return;

		Rigidbody* rb = obj->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}
}