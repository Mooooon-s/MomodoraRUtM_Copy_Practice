#include "MnCollider.h"
#include "MnGameObject.h"
#include "MnTransform.h"

namespace Mn
{
	Collider::Collider()
		:Component(eComponentType::Collider)
		,_Pos(Vector2::Zero)
		,_Center(Vector2::Zero)
		,_Size(48.0f*3,48.0f*3)
		,_Scale(Vector2::One)
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

		Rectangle(hdc, _Pos.x, _Pos.y, _Pos.x + _Size.x, _Pos.y + _Size.y);
		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
	}
	void Collider::Release()
	{
	}
	void Collider::Center(Vector2 center)
	{
		_Center = center;
	}
	void Collider::Size(Vector2 size)
	{
	}
	void Collider::Scale(Vector2 scale)
	{
	}
}