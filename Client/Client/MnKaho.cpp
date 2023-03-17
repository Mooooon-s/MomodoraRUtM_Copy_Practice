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
		//delete kahoCat;
		//delete kahoHuman;
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
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKeyDown(eKeyCode::M)&& _bIsCat==false)
		{
			_bIsCat = true;
			kahoCat->Active(true);
			kahoHuman->Active(false);
			Camera::SetTarget(kahoCat);
		}
		else if(Input::GetKeyDown(eKeyCode::M) && _bIsCat == true)
		{
			_bIsCat = false;
			kahoCat->Active(false);
			kahoHuman->Active(true);
			Camera::SetTarget(kahoHuman);
		}

		tr->Pos(_Pos);
		UpdateStatus();
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
		if (_bIsCat)
		{
			Transform* catTr = kahoCat->GetComponent<Transform>();
			_Dir = kahoCat->Dir();
			_Pos = catTr->Pos();
		}
		else
		{
			Transform* humanTr = kahoHuman->GetComponent<Transform>();
			_Dir = kahoHuman->Dir();
			_Pos = humanTr->Pos();
		}
	}
}