#include "MnObstacle.h"
#include "MnResources.h"
#include "MnImage.h"

#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnTransform.h"

#include "MnObject.h"
#include "MnMapTrriger.h"

#include "MnSceneManager.h"
#include "MnGround.h"

namespace Mn
{
	Obstacle::Obstacle()
		: GameObject()
		, _Image(nullptr)
		, _Ground(nullptr)
		, _Sound(nullptr)
		, _Animator(nullptr)
		, _Collider(nullptr)
		, _Rigidbody(nullptr)
		, _Trigger(nullptr)
		, _ObState(eObstacleState::Search)
	{
		Transform* tr = GetComponent<Transform>();
		tr->Pos(Vector2(-200,-200));
	}
	Obstacle::~Obstacle()
	{
	}
	void Obstacle::Initialize()
	{
		SetName(L"Obstacle");
		_Image = Resources::Load<Image>(L"Obstacle_Idle", L"..\\Resources\\object.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Obstacle_Idle_", _Image, Vector2::Zero, 3, 1, 3, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Obstacle_Rotate", L"..\\Resources\\object_Rotate.bmp");
		_Animator->CreateAnimation(L"Obstacle_Rotate_", _Image, Vector2::Zero, 5, 1, 5, Vector2::Zero, 0.08);
		_Image = Resources::Load<Image>(L"Obstacle_Done", L"..\\Resources\\object_Done.bmp");
		_Animator->CreateAnimation(L"Obstacle_Done_", _Image, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.08);
		_Animator->Play(L"Obstacle_Idle_", true);
		
		_Rigidbody = AddComponent<Rigidbody>();
		_Rigidbody->SetMass(0.5f);
		_Rigidbody->SetGround(true);

		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(_Image->Width()*2, _Image->Height()*2));
		Vector2 center = Vector2((_Image->Width()*2 / 2.0), (_Image->Height()*2));
		_Collider->Center(Vector2(center*-1));

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		_Trigger = object::Instantiate<MapTrriger>(pos, eLayerType::Trriger);
		_Trigger->GetComponent<Collider>()->Size(Vector2(60, 300));
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> groundObj = scene->GetGameObject(eLayerType::Ground);
		for (auto v : groundObj)
		{
			if (dynamic_cast<Ground*>(v))
			{
				_Ground = dynamic_cast<Ground*>(v)->Map();
				break;
			}
		}

		_Sound = Resources::Load<Sound>(L"DoneSound", L"..\\Resources\\Sound\\Explosion.wav");

		GameObject::Initialize();
	}
	void Obstacle::Update()
	{


		switch (_ObState)
		{
		case eObstacleState::Search:
			search();
			break;
		case eObstacleState::Trigg:
			trigg();
			break;
		case eObstacleState::Done:
			done();
			break;
		default:
			break;
		}
		GameObject::Update();
	}
	void Obstacle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Obstacle::Release()
	{
		GameObject::Release();
	}
	void Obstacle::OnCollisionEnter(Collider* other)
	{
	}
	void Obstacle::search()
	{
		Transform* Triggtr = _Trigger->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		Triggtr->Pos(pos);

		if (_Trigger->Trriger() == true)
		{
			_Rigidbody->SetGround(false);
			_ObState = eObstacleState::Trigg;
			_Animator->Play(L"Obstacle_Rotate_", true);
		}
		else
		{
			_Rigidbody->SetGround(true);
		}
	}
	void Obstacle::done()
	{
	}
	void Obstacle::trigg()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		pos.y += _Image->Height();
		COLORREF color = GetPixel(_Ground->Hdc(), pos.x, pos.y);
		if (color != RGB(0, 0, 0))
		{
			_Sound->Play(false);
			_Rigidbody->SetGround(true);
			_ObState = eObstacleState::Done;
			_Animator->Play(L"Obstacle_Done_", true);
		}
	}
}