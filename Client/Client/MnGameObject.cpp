#include "MnGameObject.h"

namespace Mn
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
		for (Component* comp : _Components)
		{
			delete comp;
			comp = nullptr;
		}
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
	}

}
