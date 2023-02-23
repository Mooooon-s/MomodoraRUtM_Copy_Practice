#include "MnGameObject.h"
#include "MnTransform.h"

namespace Mn
{
	GameObject::GameObject()
	{
		_Components.resize((UINT)eComponentType::Max);
		AddComponent<Transform>();
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
