#include "MnCollider.h"
#include "MnGameObject.h"
#include "MnTransform.h"
#include "MnCamera.h"

namespace Mn
{
	UINT Collider::ColliderNumber = 0;
	Collider::Collider()
		:Component(eComponentType::Collider)
		,_Pos(Vector2::Zero)
		,_Center(Vector2::Zero)
		,_Size(48.0f*3,48.0f*3)
		,_Scale(Vector2::One)
		,_ID(ColliderNumber++)
	{
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	
	}
	void Collider::Update()
	{
			Transform* tr = Owner()->GetComponent<Transform>();
			_Pos = tr->Pos()+ _Center;
	}
	void Collider::Render(HDC hdc)
	{
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Vector2 pos = Camera::ComputePos(_Pos);
		Rectangle(hdc, pos.x, pos.y, pos.x + _Size.x, pos.y + _Size.y);
		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
	}
	void Collider::Release()
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		Owner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		Owner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		Owner()->OnCollisionExit(other);
	}
}