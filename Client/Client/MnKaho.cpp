#include "MnKaho.h"

namespace Mn
{
	Kaho::Kaho()
		:_KahoHuman(nullptr)
		,_KahoCat(nullptr)
		,_bIsCat(false)
	{
	}
	Kaho::~Kaho()
	{
	}

	void Kaho::Initialize()
	{
		_KahoHuman = new Kaho_Human();
		_KahoCat = new Kaho_Cat();
		GameObject::Initialize();
	}

	void Kaho::Update()
	{
		if (_bIsCat)
		{
			_KahoCat->Update();
		}
		else
		{
			_KahoHuman->Update();
		}
		GameObject::Update();
	}

	void Kaho::Render(HDC hdc)
	{
		if (_bIsCat)
		{
			_KahoCat->Render(hdc);
		}
		else
		{
			_KahoHuman->Render(hdc);
		}
		GameObject::Render(hdc);
	}

	void Kaho::Release()
	{
		_KahoCat->Release();
		_KahoHuman->Release();
		GameObject::Release();
	}

	void Kaho::KahoInitialize()
	{

	}

	void Kaho::KahoUpdate()
	{
	}

	void Kaho::KahoRender(HDC hdc)
	{
	}

	void Kaho::KahoRelease()
	{
	}



}