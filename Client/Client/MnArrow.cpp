#include "MnArrow.h"
#include "MnTransform.h"
#include "MnTime.h"
#include "MnResources.h"
#include "MnImage.h"
#include "MnComponent.h"
#include "MnAnimator.h"
#include "MnObject.h"
#include "MnCollider.h"
namespace Mn
{
	Arrow::Arrow()
		: GameObject()
		,_Animator(nullptr)
		, _Collider(nullptr)
		, _Hit(false)
		, _IsEnd(false)
		, _Dir(eDir::R)
	{
	}
	Arrow::~Arrow()
	{
	}
	void Arrow::Initialize()
	{
		_Collider = AddComponent<Collider>();
		_Collider->Size(Vector2(70, 10));
		_Collider->Center(Vector2(-35, -55));

		Image* image = Resources::Load<Image>(L"Arrow", L"..\\Resources\\Arrow.bmp");
		_Animator = AddComponent<Animator>();
		_Animator->CreateAnimation(L"Arrow_Right", image, Vector2(0, 0), 2, 1, 1, Vector2::Zero, 0.08f);
		_Animator->CreateAnimation(L"Arrow_Left", image, Vector2(32, 0), 2, 1, 1, Vector2::Zero, 0.08f);
		image = Resources::Load<Image>(L"Arrow_Destroy", L"..\\Resources\\Arrow_Destroy.bmp");
		_Animator->CreateAnimation(L"Destroy", image, Vector2::Zero,4,1,4,Vector2::Zero,0.08);
		_Animator->GetCompleteEvent(L"Destroy") = std::bind(&Arrow::destroy,this);
		
	}
	void Arrow::Update()
	{
		if (_Hit == false)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->Pos();
			if (_Dir == eDir::R)
			{
				pos.x += 1000.0f * Time::DeltaTime();
				tr->Pos(pos);
				_Animator->Play(L"Arrow_Right", false);
			}
			else
			{
				pos.x -= 1000.0f * Time::DeltaTime();
				tr->Pos(pos);
				_Animator->Play(L"Arrow_Left", false);
			}
		}
		if(_IsEnd)
		{
			GameObject::State(eState::Death);
		}
		GameObject::Update();
	}
	void Arrow::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->Pos();
		Rectangle(hdc, pos.x, pos.y, pos.x + 5, pos.y + 5);
		GameObject::Render(hdc);
	}
	void Arrow::Release()
	{
		GameObject::Release();
	}
	void Arrow::OnCollisionEnter(Collider* other)
	{
		if (other->Owner()->GetName() == L"Enemy" || other->Owner()->GetName() == L"Boss")
		{
			_Hit = true;
			//_Animator->Play(L"Destroy", false);
		}
	}
	void Arrow::Hit()
	{
		_IsEnd = true;
		//GameObject::State(eState::Death);
	}
	void Arrow::destroy()
	{
		_IsEnd = true;
	}
}