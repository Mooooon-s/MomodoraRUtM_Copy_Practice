#include "MnCollisionManager.h"
#include "MnSceneManager.h"
#include "MnScene.h"

namespace Mn
{
	WORD CollisionManager::_Matrix[(UINT)eLayerType::Max] = {};
	std::map<UINT64, bool> CollisionManager::_CollisionMap;

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

				ColliderCollision(leftCollider, rightCollider, left, right);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right)
	{
		ColliderID colliderID = {};
		colliderID.left = (UINT)leftCol->GetID();
		colliderID.right = (UINT)rightCol->GetID();

		std::map<UINT64, bool>::iterator iter
			= _CollisionMap.find(colliderID.id);

		if (iter == _CollisionMap.end())
		{
			_CollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = _CollisionMap.find(colliderID.id);
		}

		if (Intersect(leftCol, rightCol))
		{
			// 최초 충돌 시작했을때 enter
			if (iter->second == false)
			{
				leftCol->OnCollisionEnter(rightCol);
				rightCol->OnCollisionEnter(leftCol);

				iter->second = true;
			}
			else // 충돌 중인상태 stay
			{
				leftCol->OnCollisionStay(rightCol);
				rightCol->OnCollisionStay(leftCol);
			}
		}
		else
		{
			// Exit
			// 이전프레임 충돌 O
			// 현재는 충돌 X 
			if (iter->second == true)
			{
				leftCol->OnCollisionExit(rightCol);
				rightCol->OnCollisionExit(leftCol);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->Pos();
		Vector2 rightPos = right->Pos();

		Vector2 leftSize = left->Size();
		Vector2 rightSize = right->Size();

		leftPos.x = leftPos.x + leftSize.x / 2.0f;
		leftPos.y = leftPos.y + leftSize.y / 2.0f;

		rightPos.x = rightPos.x+ rightSize.x / 2.0f;
		rightPos.y = rightPos.y+ rightSize.y / 2.0f;

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
		memset(_Matrix, 0, sizeof(WORD) * (UINT)eLayerType::Max);
		_CollisionMap.clear();
	}




}
