#include "MnMagArrow.h"
#include "MnImage.h"
#include "MnResources.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnSound.h"

namespace Mn
{
	MagArrow::MagArrow()
		: GameObject()
		, _Arrow(nullptr)
		, _BlowUpArrow(nullptr)
		, _Collider(nullptr)
		, _BlowUp(false)
		, _Timer(0.0f)
	{
	}
	MagArrow::~MagArrow()
	{
	}
	void MagArrow::Initialize()
	{
		SetName(L"Throws");
		GameObject::Initialize();
		_Arrow = Resources::Load<Image>(L"MagArrow", L"..\\Resources\\Magnolia-Throws_2.bmp");
		_BlowUpArrow = Resources::Load<Image>(L"MagArrow2", L"..\\Resources\\Magnolia-Throws_1.bmp");
		Sound* ArrowSound = Resources::Load<Sound>(L"ArrowSound", L"..\\Resources\\Sound\\Kaho_Human\\Shoot_Arrow.wav");
		ArrowSound->Play(false);
		_Collider = AddComponent<Collider>();
	}
	void MagArrow::Update()
	{
		if (_BlowUp)
		{
			_Collider->Size(Vector2(10,66));
		}
		else
		{
			_Collider->Size(Vector2(10,66));
		}
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		pos.y += 600.0f * Time::DeltaTime();
		Tr->Pos(pos);

		_Timer += Time::DeltaTime();
		if (_Timer >= 5)
			this->State(eState::Death);

		GameObject::Update();
	}
	void MagArrow::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		if (_BlowUp)
		{
			TransparentBlt(hdc, pos.x - _BlowUpArrow->Width(), pos.y, _BlowUpArrow->Width()*2, _BlowUpArrow->Height()*2, _BlowUpArrow->Hdc(), 0, 0, _BlowUpArrow->Width(), _BlowUpArrow->Height(), RGB(0, 128, 128));
		}
		else
		{
			TransparentBlt(hdc, pos.x - _Arrow->Width(), pos.y, _Arrow->Width() * 2, _Arrow->Height() * 2, _Arrow->Hdc(), 0, 0, _Arrow->Width(), _Arrow->Height(), RGB(0, 128, 128));
		}
		GameObject::Render(hdc);
	}
	void MagArrow::Release()
	{
		GameObject::Release();
	}
	void MagArrow::OnCollisionEnter(Collider* other)
	{
	}
}