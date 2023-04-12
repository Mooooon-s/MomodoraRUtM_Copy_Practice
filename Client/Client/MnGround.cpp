#include "MnGround.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"
#include "MnKaho.h"
#include "MnCollider.h"
#include "MnRigidbody.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnSceneManager.h"
#include "MnTime.h"
#include "MnCamera.h"
#include "Application.h"

extern Mn::Application application;

namespace Mn
{
	Ground::Ground()
		: _Image(nullptr)
		, _Player(nullptr)
		, _Cat(nullptr)
		, _Human(nullptr)
		, _PlayerPos(Vector2::Zero)
		, _MoveSpeed(0.0f)
	{
	}
	Ground::~Ground()
	{
	}
	void Ground::Initialize()
	{
		Scene* scene = SceneManager::ActiveScene();
		if (scene->GetName() == L"PlayScene")
			_Image = Resources::Load<Image>(L"PlayTile_Pixel", L"..\\Resources\\Test_Ground_Pixel.bmp");
		if(scene->GetName()==L"BossScene")
			_Image = Resources::Load<Image>(L"BossTile_Pixel", L"..\\Resources\\Test_Map.bmp");
		GameObject::SetName(L"Ground");
		GameObject::Initialize();

		std::vector<GameObject*> playerobj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerobj)
		{
			if (dynamic_cast<Kaho*>(v))
				_Player = dynamic_cast<Kaho*>(v);
			if (dynamic_cast<Kaho_Cat*>(v))
				_Cat = dynamic_cast<Kaho_Cat*>(v);
			if (dynamic_cast<Kaho_Human*>(v))
				_Human = dynamic_cast<Kaho_Human*>(v);
		}
	}
	void Ground::Update()
	{
		if (_Player->CameraTarget<GameObject>()->GetComponent<Transform>() != nullptr)
		{
			Transform* playerTr = _Player->CameraTarget<GameObject>()->GetComponent<Transform>();
			Vector2 pos = playerTr->Pos();
			Vector2 underpos = Vector2(pos.x,pos.y + 3);
			Vector2 sidepos = Vector2(pos.x - _Size.x/2,pos.y-_Size.y / 2.0f);
			Vector2 upperpos = Vector2(pos.x, pos.y - _Size.y);

			if (_Player->IsCat())
			{
				_Size = _Cat->GetComponent<Collider>()->Size();
				_MoveSpeed = _Cat->MoveSpeed();
			}
			else
			{
				_Size=_Human->GetComponent<Collider>()->Size();
				_MoveSpeed = _Human->MoveSpeed();
			}

			//find color
			COLORREF color = _Image->GetPixel(pos.x, pos.y);
			COLORREF Footcolor = _Image->GetPixel(underpos.x, underpos.y);
			COLORREF rightColor = _Image->GetPixel(pos.x-_Size.x/2.0f, pos.y-_Size.y/2.0f);
			COLORREF leftColor = _Image->GetPixel(pos.x+_Size.x/2.0f, pos.y-_Size.y/2.0f);
			COLORREF upColor = _Image->GetPixel(upperpos.x, upperpos.y);
			Rigidbody* rb = _Player->GetRigidbody<GameObject>()->GetComponent<Rigidbody>();
			if (color == RGB(255, 0, 255))
			{
				rb->SetGround(true);
				Vector2 pos = playerTr->Pos();
				pos.y -= 1;
				playerTr->Pos(pos);
			}
			if(Footcolor!=RGB(255,0,255))
			{
				rb->SetGround(false);
			}
			if (rightColor == RGB(0, 0, 255))
			{
				Vector2 pos = playerTr->Pos();
				pos.x += _MoveSpeed * Time::DeltaTime();
				playerTr->Pos(pos);
			}
			if (leftColor == RGB(0, 0, 255))
			{
				Vector2 pos = playerTr->Pos();
				pos.x -= _MoveSpeed * Time::DeltaTime();
				playerTr->Pos(pos);
			}
			if (upColor == RGB(0, 255, 0))
			{
				if (_Player->IsCat())
				{
					_Cat->GetComponent<Rigidbody>()->Velocity(Vector2::Zero);
					_Cat->PlayerStatus(ePlayerStatus::Fall);

				}
				else
				{
					_Human->GetComponent<Rigidbody>()->Velocity(Vector2::Zero);
					_Cat->PlayerStatus(ePlayerStatus::Fall);
				}
			}
		}
		GameObject::Update();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Camera::ComputePos(tr->Pos());

		TransparentBlt(hdc, pos.x, pos.y
			, _Image->Width(), _Image->Height()
			, _Image->Hdc()
			, 0, 0
			, _Image->Width(), _Image->Height()
			, RGB(0, 0, 0));

		Transform* playerTr = _Player->CameraTarget<GameObject>()->GetComponent<Transform>();
		Vector2 ppos = playerTr->Pos();
		Vector2 underpos = Vector2(ppos.x, ppos.y + 3);
		Vector2 lsidepos = Vector2(ppos.x - _Size.x/2, ppos.y - _Size.y / 2.0f);
		Vector2 rsidepos = Vector2(ppos.x + _Size.x / 2, ppos.y - _Size.y / 2.0f);
		Vector2 upperpos = Vector2(ppos.x, ppos.y - _Size.y);

		Rectangle(hdc, ppos.x, ppos.y, ppos.x + 2, ppos.y + 2);
		Rectangle(hdc, underpos.x, underpos.y, underpos.x + 5, underpos.y + 5);
		Rectangle(hdc, lsidepos.x, lsidepos.y, lsidepos.x + 10, lsidepos.y + 10);
		Rectangle(hdc, rsidepos.x, rsidepos.y, rsidepos.x + 10, rsidepos.y + 10);
		Rectangle(hdc, upperpos.x, upperpos.y, upperpos.x + 10, upperpos.y + 10);

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
		if (rb != nullptr)
		{
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
		if(rb!=nullptr)
			rb->SetGround(false);
	}
}