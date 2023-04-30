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
#include "MnAnimator.h"
#include "MnArrow.h"
#include "MnKnife.h"
#include "MnStage2_1.h"

#include "MnMagnolia.h"
#include "MnMagnoliaBoss.h"
#include "MnCatPeasant.h"

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
			_Image = Resources::Load<Image>(L"Stage1_0_Pixel", L"..\\Resources\\Start_Scene.bmp");
		if(scene->GetName()==L"Stage1_1")
			_Image = Resources::Load<Image>(L"Stage1_1_Pixel", L"..\\Resources\\Stage1_1.bmp");
		if (scene->GetName() == L"Stage1_2")
			_Image = Resources::Load<Image>(L"Stage1_2_Pixel", L"..\\Resources\\Stage1_2.bmp");
		if (scene->GetName() == L"Stage1_3")
			_Image = Resources::Load<Image>(L"Stage1_3_Pixel", L"..\\Resources\\Stage1_3.bmp");
		if (scene->GetName() == L"Stage1_Boss")
			_Image = Resources::Load<Image>(L"Stage1_Boss_Pixel", L"..\\Resources\\Stage1_Boss.bmp");
		if (scene->GetName() == L"Stage2_1")
			_Image = Resources::Load<Image>(L"Stage2_1_Pixel", L"..\\Resources\\Stage2_1.bmp");
		if (scene->GetName() == L"Stage2_2")
			_Image = Resources::Load<Image>(L"Stage2_2_Pixel", L"..\\Resources\\Stage2_2.bmp");
		if (scene->GetName() == L"Stage2_3")
			_Image = Resources::Load<Image>(L"Stage2_3_Pixel", L"..\\Resources\\Stage2_3.bmp");
		if (scene->GetName() == L"Stage3_1")
			_Image = Resources::Load<Image>(L"Stage3_1_Pixel", L"..\\Resources\\Stage3_1.bmp");
		if (scene->GetName() == L"Stage3_2")
			_Image = Resources::Load<Image>(L"Stage3_2_Pixel", L"..\\Resources\\Stage3_2.bmp");
		if (scene->GetName() == L"Stage3_3")
			_Image = Resources::Load<Image>(L"Stage3_3_Pixel", L"..\\Resources\\Stage3_3.bmp");
		if (scene->GetName() == L"Ending")
			_Image = Resources::Load<Image>(L"Stage_Ending_Pixel", L"..\\Resources\\Ending.bmp");

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
		//---------------------------------------------------------------------------------------------
		//
		//										Player
		//
		//---------------------------------------------------------------------------------------------
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
			COLORREF rightColor = _Image->GetPixel(pos.x-_Size.x/2.0f, pos.y-_Size.y/4.0f);
			COLORREF leftColor = _Image->GetPixel(pos.x+_Size.x/2.0f, pos.y-_Size.y/4.0f);
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
			if (Footcolor == RGB(255, 0, 0))
			{
				if (_Player->IsCat())
				{
					_Cat->SyncHp(0);
				}
				else
				{
					_Human->SyncHp(0);
				}
				rb->SetGround(true);
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
		////-----------------------------------------------------------------------------------------------------
		////
		////											Monster
		////
		////-----------------------------------------------------------------------------------------------------
		Scene* scene = SceneManager::ActiveScene();
		std::vector<GameObject*> monObj = scene->GetGameObject(eLayerType::Monster);
		for (auto v : monObj)
		{
			if (dynamic_cast<Magnolia*>(v) || dynamic_cast<CatPeasant*>(v) || dynamic_cast<MagnoliaBoss*>(v))
			{
				continue;
			}
			Transform* tr = v->GetComponent<Transform>();
			Vector2 monPos = tr->Pos();
			COLORREF monfootColor = ::GetPixel(_Image->Hdc(), monPos.x, monPos.y);
			if (monfootColor == RGB(255, 0, 255))
			{
				Rigidbody* monRb = v->GetComponent<Rigidbody>();
				monRb->SetGround(true);
				monPos.y -= 1;
				tr->Pos(monPos);
			}
			if (monfootColor != RGB(255, 0, 255))
			{
				Rigidbody* monRb = v->GetComponent<Rigidbody>();
				monRb->SetGround(false);
			}
		}
		////-----------------------------------------------------------------------------------------------------
		////
		////											NPC
		////
		////-----------------------------------------------------------------------------------------------------
		scene = SceneManager::ActiveScene();
		std::vector<GameObject*> NpcObj = scene->GetGameObject(eLayerType::NPC);
		for (auto v : NpcObj)
		{
			Transform* tr = v->GetComponent<Transform>();
			Vector2 NpcPos = tr->Pos();
			COLORREF NpcfootColor = ::GetPixel(_Image->Hdc(), NpcPos.x, NpcPos.y);
			if (NpcfootColor == RGB(255, 0, 255))
			{
				Rigidbody* NpcRb = v->GetComponent<Rigidbody>();
				NpcRb->SetGround(true);
				NpcPos.y -= 1;
				tr->Pos(NpcPos);
			}
			if (NpcfootColor != RGB(255, 0, 255))
			{
				Rigidbody* NpcRb = v->GetComponent<Rigidbody>();
				NpcRb->SetGround(false);
			}
		}
		//-----------------------------------------------------------------------------------------------------
		//
		//												Throws
		//
		//-----------------------------------------------------------------------------------------------------
		scene = SceneManager::ActiveScene();
		std::vector<GameObject*> attackObj = scene->GetGameObject(eLayerType::Throws);
		for (auto v : attackObj)
		{
			if (dynamic_cast<Arrow*>(v))
			{
				auto a = dynamic_cast<Arrow*>(v);
				Transform* tr = a->GetComponent<Transform>();
				Vector2 attackPos = tr->Pos();
				COLORREF attackColor = ::GetPixel(_Image->Hdc(), attackPos.x, attackPos.y);
				if (attackColor != RGB(0, 0, 0))
				{
					a->Hit();
				}
			}
			if (dynamic_cast<Knife*>(v))
			{
				auto a = dynamic_cast<Knife*>(v);
				Transform* tr = a->GetComponent<Transform>();
				Vector2 attackPos = tr->Pos();
				COLORREF attackColor = ::GetPixel(_Image->Hdc(), attackPos.x, attackPos.y);
				if (attackColor != RGB(0, 0, 0))
				{
					a->Hit();
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
		Vector2 lsidepos = Vector2(ppos.x - _Size.x/2, ppos.y - _Size.y / 4.0f);
		Vector2 rsidepos = Vector2(ppos.x + _Size.x / 2, ppos.y - _Size.y / 4.0f);
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