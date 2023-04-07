#include "MnGround.h"
#include "MnCollider.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"
#include "MnKaho.h"
#include "MnRigidbody.h"
#include "MnTransform.h"
#include "MnResources.h"
#include "MnSceneManager.h"
#include "MnCamera.h"

#include "Application.h"

extern Mn::Application application;

namespace Mn
{
	Ground::Ground()
		: _Image(nullptr)
		, _Player(nullptr)
		, _PlayerPos(Vector2::Zero)
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
			_Image = Resources::Load<Image>(L"BossTile_Pixel", L"..\\Resources\\Underground_stage_Pixel.bmp");
		GameObject::SetName(L"Ground");
		GameObject::Initialize();

		std::vector<GameObject*> playerobj = scene->GetGameObject(eLayerType::Player);
		for (auto v : playerobj)
		{
			if (dynamic_cast<Kaho*>(v))
				_Player = dynamic_cast<Kaho*>(v);
		}
	}
	void Ground::Update()
	{
		GameObject::Update();
		if (_Player->CameraTarget<GameObject>()->GetComponent<Transform>() != nullptr)
		{
			Transform* playerTr = _Player->CameraTarget<GameObject>()->GetComponent<Transform>();
			Vector2 pos = playerTr->Pos();
			Vector2 underpos = Vector2(pos.x,pos.y + 3);
			//Vector2 pos = Camera::ComputePos(playerTr->Pos());
			COLORREF color = _Image->GetPixel(pos.x, pos.y);
			COLORREF Footcolor = _Image->GetPixel(underpos.x, underpos.y);

			Rigidbody* rb = _Player->GetRigidbody<GameObject>()->GetComponent<Rigidbody>();
			if (color == RGB(255, 0, 255))
			{
				rb->SetGround(true);
				Vector2 pos = playerTr->Pos();
				pos.y -= 1;
				playerTr->Pos(pos);
			}
			else if(Footcolor!=RGB(255,0,255))
			{
				rb->SetGround(false);
			}
		}
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