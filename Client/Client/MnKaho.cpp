#include "MnKaho.h"
#include "MnInput.h"
#include "MnKaho_Cat.h"
#include "MnKaho_Human.h"
#include "MnComponent.h"
#include "MnTransform.h"
#include "MnCamera.h"

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
		_Pos = Vector2(400.0f, 400.0f);
		tr->Pos(_Pos);
		kahoCat = new Kaho_Cat();
		kahoHuman = new Kaho_Human();
		kahoCat->Initialize();
		kahoHuman->Initialize();
		GameObject::Initialize();
	}

	void Kaho::Update()
	{
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKeyDown(eKeyCode::M)&& _bIsCat==false)
		{
			_bIsCat = true;
		}
		else if(Input::GetKeyDown(eKeyCode::M) && _bIsCat == true)
		{
			_bIsCat = false;
		}

		if (_bIsCat)
		{
			Transform* catTr = kahoCat->GetComponent<Transform>();
			catTr->Pos(_Pos);
			kahoCat->Update();
			_Pos = catTr->Pos();
			tr->Pos(_Pos);
		}
		else
		{

			Transform* humanTr = kahoHuman->GetComponent<Transform>();
			humanTr->Pos(_Pos);
			kahoHuman->Update();
			_Pos = humanTr->Pos();
			tr->Pos(_Pos);
		}
	
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
	}

	void Kaho::Release()
	{
		GameObject::Release();
	}

}