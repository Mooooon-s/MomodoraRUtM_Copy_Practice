#include "MnCollisionManager.h"
#include "MnSceneManager.h"
#include "MnCollider.h"
namespace Mn
{
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::ActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
			{
				if (_Matrix[row] & (1 << col))
				{
					LayerCollision(scene,(eLayerType)row,(eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObject(left);
		const std::vector<GameObject*>& rights = scene->GetGameObject(right);

		for (auto leftObj : lefts)
		{
			Collider* leftCollider = leftObj->GetComponent<Collider>();
			if (leftCollider == nullptr)
				continue;

			for (auto rightObj : rights)
			{
				Collider* rightCollider = rightObj->GetComponent<Collider>();
				if (rightCollider == nullptr)
					continue;

				if (leftObj == rightObj)
					continue;
				if (Intersect(leftCollider, rightCollider))
				{
					//충돌
				}
				else
				{
					//미충돌
				}
				
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->Pos();
		Vector2 rightPos = right->Pos();

		Vector2 leftSize = left->Size();
		Vector2 rightSize = right->Size();

		if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
		{
			return true;
		}

		return false;

	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool value)
	{
		UINT row = 0;
		UINT col = 0;

		UINT ileft = (UINT)left;
		UINT iright = (UINT)right;

		if (left <= right)
		{
			row = ileft;
			col = iright;
		}
		else
		{
			row = iright;
			col = ileft;
		}

		if (value == true)
			_Matrix[row] |= (1 << col);
		else
			_Matrix[row] &= ~(1 << col);

	}

	void CollisionManager::Clear()
	{
	}




}
