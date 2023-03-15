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
		delete kahoCat;
		delete kahoHuman;
	}

	void Kaho::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		_Pos=tr->Pos();
		_Pos = Vector2(700.0f,400.0f);
		tr->Pos(_Pos);

		kahoCat = new Kaho_Cat();
		kahoHuman = new Kaho_Human();
		kahoCat->Initialize();
		kahoHuman->Initialize();

		_KahoColl = AddComponent<Collider>();
		_KahoColl->Center(Vector2(-12.0f * 3, -40.0f * 3));
		_KahoColl->Size(Vector2(24.0f * 3, 40.0f * 3));


		GameObject::Initialize();
	}

	void Kaho::Update()
	{
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKeyDown(eKeyCode::M)&& _bIsCat==false)
		{
			_KahoColl->Size(Vector2(32.0f * 3, 16.0f * 3));
			_KahoColl->Center(Vector2(-16.0f*3,-16.0f*3));
			_bIsCat = true;
		}
		else if(Input::GetKeyDown(eKeyCode::M) && _bIsCat == true)
		{
			_KahoColl->Center(Vector2(-12.0f * 3, -40.0f * 3));
			_KahoColl->Size(Vector2(24.0f * 3, 40.0f * 3));
			_bIsCat = false;
		}

		UpdateStatus();
		_KahoColl->Update();
		tr->Pos(_Pos);
	}

	void Kaho::Render(HDC hdc)
	{
		if (_bIsCat)
		{
			kahoCat->Render(hdc);
		}
		else
		{
			kahoHuman->Render(hdc);
		}
		_KahoColl->Render(hdc);
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
			catTr->Pos(_Pos);
			kahoCat->Dir(_Dir);

			kahoCat->Update();
			
			_Dir = kahoCat->Dir();
			_Pos = catTr->Pos();
		}
		else
		{
			Transform* humanTr = kahoHuman->GetComponent<Transform>();
			humanTr->Pos(_Pos);
			kahoHuman->Dir(_Dir);
			
			kahoHuman->Update();
			
			_Dir = kahoHuman->Dir();
			_Pos = humanTr->Pos();
		}
	}

}