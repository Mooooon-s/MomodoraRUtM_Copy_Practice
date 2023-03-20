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
		Kaho_Human* kahoHuman = dynamic_cast<Kaho_Human*>(other->Owner());
		if (kahoHuman == nullptr)
			return;

		Rigidbody* rb = kahoHuman->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* kahoHumanColl = kahoHuman->GetComponent<Collider>();
		Vector2 kahoHumanPos = kahoHumanColl->Pos();

		Collider* groundColl = this->GetComponent<Collider>();
		Vector2 groundPos = groundColl->Pos();

		float fLen = fabs(kahoHumanPos.y - groundPos.y);
		float fSize = (kahoHumanColl->Size().y / 2.0f + groundColl->Size().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* kahoHumanTr = kahoHuman->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 kahoHumanPos = kahoHumanTr->Pos();
			Vector2 grPos = grTr->Pos();

			kahoHumanPos -= (fSize - fLen) - 1.0f;
			kahoHumanTr->Pos(kahoHumanPos);
		}

	}
	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
		Kaho_Human* kahoHuman = dynamic_cast<Kaho_Human*>(other->Owner());
		if (kahoHuman == nullptr)
			return;

		Rigidbody* rb = kahoHuman->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}
}