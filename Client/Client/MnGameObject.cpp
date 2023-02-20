#include "MnGameObject.h"

namespace Mn
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		for (auto comp : _Components) {
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto comp : _Components) {
			if (comp == nullptr)
				continue;
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (auto comp : _Components) {
			if (comp == nullptr)
				continue;
			comp->Render(hdc);
		}
	}

	void GameObject::Release()
	{
		for (auto comp : _Components) {
			if (comp == nullptr)
				continue;
			comp->Release();
		}
	}

}
