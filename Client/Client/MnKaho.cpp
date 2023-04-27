#include "MnKaho.h"
#include "MnInput.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnCamera.h"
#include "MnCollisionManager.h"

namespace Mn
{
	Kaho::Kaho()
		: _bIsCat(false)
		, kahoCat(nullptr)
		, kahoHuman(nullptr)
		, _Swap(false)
		, _Dir(eDir::R)
		, _Hp(100)
	{
	}
	Kaho::~Kaho()
	{
	}

	void Kaho::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos = Vector2(700.0f,400.0f);
		tr->Pos(_Pos);
		GameObject::Initialize();
	}

	void Kaho::Update()
	{
		UpdateStatus();
		Transform* tr = GetComponent<Transform>();
		if (kahoHuman->Switch()==true && _bIsCat==false)
		{
			kahoCat->Dir(_Dir);
			_bIsCat = true;
			kahoCat->Active(eState::Active);
			kahoHuman->Active(eState::Pause);
			kahoHuman->PlayerStatus(ePlayerStatus::Idle);
			kahoHuman->Switch(false);
			kahoCat->SyncHp(_Hp);
			kahoCat->animationCtrl();
			//if(Camera::GetTarget()!=nullptr)
				//Camera::SetTarget(kahoCat);
		}
		else if(kahoCat->Switch()==true && _bIsCat == true)
		{
			kahoHuman->Dir(_Dir);
			_bIsCat = false;
			kahoCat->Active(eState::Pause);
			kahoHuman->Active(eState::Active);
			kahoCat->PlayerStatus(ePlayerStatus::Idle);
			kahoCat->Switch(false);
			kahoHuman->SyncHp(_Hp);
			kahoHuman->animationCtrl();
			//if (Camera::GetTarget() != nullptr)
				//Camera::SetTarget(kahoHuman);
		}
		if (_Swap==false && _bIsCat == true)
		{
			kahoCat->Dir(_Dir);
			_bIsCat = true;
			kahoCat->SyncHp(_Hp);
			kahoCat->Active(eState::Active);
			kahoHuman->Active(eState::Pause);
			kahoHuman->PlayerStatus(ePlayerStatus::Idle);
			kahoCat->animationCtrl();
			//if (Camera::GetTarget() != nullptr)
				//Camera::SetTarget(kahoCat);
			_Swap = true;
		}
		else if(_Swap == false && _bIsCat == false)
		{
			kahoHuman->SyncHp(_Hp);
			_Swap = true;
		}
		tr->Pos(_Pos);
		if (_bIsCat == false)
			_Hp = kahoHuman->SyncHp();
		else
			_Hp =kahoCat->SyncHp();
	}

	void Kaho::Render(HDC hdc)
	{
	}

	void Kaho::Release()
	{
		GameObject::Release();
	}

	void Kaho::UpdateStatus()
	{
		Transform* catTr = kahoCat->GetComponent<Transform>();
		Transform* humanTr = kahoHuman->GetComponent<Transform>();
		if (!_bIsCat)
		{
			kahoCat->Dir(_Dir);
			catTr->Pos(_Pos);
			_Pos = humanTr->Pos();
			_Dir = kahoHuman->Dir();
		}
		else
		{
			kahoHuman->Dir(_Dir);
			humanTr->Pos(_Pos);
			_Pos = catTr->Pos();
			_Dir = kahoCat->Dir();
		}
	}
	int Kaho::KahoDir()
	{
		if (_bIsCat)
			return (int)kahoCat->Dir();
		else
			return (int)kahoHuman->Dir();
	}
	Vector2 Kaho::KahoColliderSize()
	{
		if (_bIsCat)
			return kahoCat->GetComponent<Collider>()->Size();
		else
			return kahoHuman->GetComponent<Collider>()->Size();
	}
}