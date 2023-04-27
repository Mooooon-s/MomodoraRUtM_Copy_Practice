#include "MnWall.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnImage.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnCamera.h"
namespace Mn
{
	Wall::Wall()
		: GameObject()
		, _Image(nullptr)
		, _Collider(nullptr)
		, _Timer(0.0f)
		, _Num(0)
	{
	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
		SetName(L"Wall");

		_Image = Resources::Load<Image>(L"Wall", L"..\\Resources\\Wall.bmp");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(50, 720));
		GameObject::Initialize();
	}
	void Wall::Update()
	{
		if (SceneManager::GetWall() == true)
			this->State(eState::Death);
		GameObject::Update();
	}
	void Wall::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 Pos = tr->Pos();
		Pos =Camera::ComputePos(Pos);
		_Timer += Time::DeltaTime();
		if (_Timer >= 1.0f)
		{
			_Num++;
			_Timer = 0;
		}
		TransparentBlt(hdc, Pos.x, Pos.y, _Image->Width() / 4, _Image->Height(), _Image->Hdc(), (_Image->Width() / 4)*_Num, 0, _Image->Width() / 4, _Image->Height(),RGB(0,128,128));
		if (_Num >= 3)
			_Num = 0;
		GameObject::Render(hdc);
	}
	void Wall::Release()
	{
		GameObject::Release();
	}
	void Wall::OnCollisionEnter(Collider* other)
	{
	}
	void Wall::OnCollisionStay(Collider* other)
	{
	}
}