#include "MnFireBall.h"
#include "MnImage.h"
#include "MnResources.h"
#include "MnTransform.h"
#include "MnComponent.h"
#include "MnCollider.h"
#include "MnTime.h"
#include "MnCamera.h"
#include "MnSceneManager.h"
#include "MnArsonist.h"

namespace Mn
{
	FireBall::FireBall()
		:GameObject()
		, _FireBall(nullptr)
		, _Degree(0)
		, _Pos(Vector2::Zero)
		, _Timer(0.0f)
		, _Boss(nullptr)
		, _First(false)
		, _Collider(nullptr)
	{
	}
	FireBall::~FireBall()
	{
	}
	void FireBall::Initialize()
	{
		SetName(L"Throws");
		_FireBall = Resources::Load<Image>(L"Fire_Ball", L"..\\Resources\\FireBall.bmp");
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(_FireBall->Width()*3, _FireBall->Height()*3));
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> BossObj = scene->GetGameObject(eLayerType::Monster);
		for (auto v : BossObj)
		{
			if (dynamic_cast<Arsonist*>(v))
			{
				_Boss = dynamic_cast<Arsonist*>(v);
				break;
			}
		}
		GameObject::Initialize();
	}
	void FireBall::Update()
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		Vector2 dir = _Pos - pos;
		dir.Normalize();
		_Degree +=Time::DeltaTime()*500.0f;
		pos.x += 600.0f * Time::DeltaTime()*dir.x;
		pos.y -= sinf(_Degree * PI/180);
		Tr->Pos(pos);
		_Timer += Time::DeltaTime();
		if (_Timer >= 3.0f && _First==true)
		{
			_Boss->Teleport(true);
			this->State(eState::Death);
		}
		if (_Timer >=3.5f)
			this->State(eState::Death);
		GameObject::Update();
	}
	void FireBall::Render(HDC hdc)
	{
		Transform* Tr = GetComponent<Transform>();
		Vector2 pos = Tr->Pos();
		pos = Camera::ComputePos(pos);
		TransparentBlt(hdc, pos.x, pos.y, _FireBall->Width()*3, _FireBall->Height()*3, _FireBall->Hdc(),0,0, _FireBall->Width(), _FireBall->Height(), RGB(0, 128, 128));
		GameObject::Render(hdc);
	}
	void FireBall::Release()
	{
		GameObject::Release();
	}
	void FireBall::OnCollisionEnter(Collider* other)
	{
	}
}