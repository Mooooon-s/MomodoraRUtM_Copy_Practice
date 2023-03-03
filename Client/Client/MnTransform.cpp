#include "MnTransform.h"

namespace Mn
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		,_Scale(Vector2(3.0f,3.0f))
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::Render(HDC hdc)
	{
	}

	void Transform::Release()
	{
	}
}