#include "MnBell.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnTransform.h"
#include "MnCamera.h"
namespace Mn
{
	Bell::Bell()
		: GameObject()
		, _Image(nullptr)
		, _BellUI(nullptr)
		, _BellNumber(1)
		, _Collider(nullptr)
		, _ON(false)
	{
	}
	Bell::~Bell()
	{
	}
	void Bell::Initialize()
	{
		SetName(L"Bell");
		_Image = Resources::Load<Image>(L"Bell", L"..\\Resources\\Bell.bmp");
		_BellUI = Resources::Load<Image>(L"BellUI", L"..\\Resources\\PrayUI.bmp");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(_Image->Width(),_Image->Height()*3));
		Vector2 pos = Vector2(_Image->Width() / 2, (_Image->Height() * 3));
		_Collider->Center(pos*-1);

		GameObject::Initialize();
	}
	void Bell::Update()
	{
		GameObject::Update();
	}
	void Bell::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		pos.x -= (_Image->Width() / 3)*3 / 2;
		pos.y -= _Image->Height()*3;
		pos = Camera::ComputePos(pos);
		switch (_BellNumber)
		{
		case 1:
			TransparentBlt(hdc, pos.x, pos.y, (_Image->Width() / 3)*3, _Image->Height()*3, _Image->Hdc(), 0, 0, _Image->Width() / 3, _Image->Height(), RGB(0, 128, 128));
			break;
		case 2:
			TransparentBlt(hdc, pos.x, pos.y, (_Image->Width() / 3)*3, _Image->Height()*3, _Image->Hdc(), 48, 0, _Image->Width() / 3, _Image->Height(), RGB(0, 128, 128));
			break;
		case 3:
			TransparentBlt(hdc, pos.x, pos.y, (_Image->Width() / 3)*3, _Image->Height()*3, _Image->Hdc(), 48*2, 0, _Image->Width() / 3, _Image->Height(), RGB(0, 128, 128));
			break;
		default:
			break;
		}
		if (_ON)
		{
			TransparentBlt(hdc, pos.x- _BellUI->Width()/5, pos.y- _BellUI->Height(), _BellUI->Width(), _BellUI->Height(), _BellUI->Hdc(), 0, 0, _BellUI->Width(), _BellUI->Height(), RGB(0, 128, 128));
		}
		GameObject::Render(hdc);
	}
	void Bell::Release()
	{
		GameObject::Release();
	}
	void Bell::OnCollisionStay(Collider* other)
	{
		if (other->Owner()->GetName() == L"Player")
		{
			_ON = true;
		}
	}
	void Bell::OnCollisionExit(Collider* other)
	{
		if (other->Owner()->GetName() == L"Player")
		{
			_ON = false;
		}
	}
}