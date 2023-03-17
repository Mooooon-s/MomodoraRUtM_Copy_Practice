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
		:_bIsCat(false)
		,kahoCat(nullptr)
		,kahoHuman(nullptr)
	{
	}
	Kaho::~Kaho()
	{
	}

	void Kaho::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos=tr->Pos();
		_Pos = Vector2(700.0f,400.0f);
		tr->Pos(_Pos);
		Camera::SetTarget(kahoHuman);
		GameObject::Initialize();
	}

	void Kaho::Update()
	{
		UpdateStatus();
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKeyDown(eKeyCode::M)&& _bIsCat==false)
		{
			kahoCat->Dir(_Dir);
			_bIsCat = true;
			kahoCat->Active(true);
			kahoHuman->Active(false);
			kahoHuman->animationCtrl();
			Camera::SetTarget(kahoCat);
		}
		else if(Input::GetKeyDown(eKeyCode::M) && _bIsCat == true)
		{
			kahoHuman->Dir(_Dir);
			_bIsCat = false;
			kahoCat->Active(false);
			kahoHuman->Active(true);
			kahoHuman->animationCtrl();
			Camera::SetTarget(kahoHuman);
		}

		tr->Pos(_Pos);
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
}