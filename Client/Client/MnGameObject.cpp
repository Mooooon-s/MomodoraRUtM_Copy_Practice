#include "MnGameObject.h"
#include "MnTransform.h"

namespace Mn
{
	GameObject::GameObject()
		:_State(eState::Active)
	{
		_Components.resize((UINT)eComponentType::Max);
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : _Components)
		{
			if (comp == nullptr)
				continue;
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : _Components) {
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

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}

	void GameObject::OnCollisionStay(Collider* other)
	{
	}

	void GameObject::OnCollisionExit(Collider* other)
	{
	}

}
