#pragma once
#include "Commoninclude.h"
#include "MnCollider.h"
#include "MnEnum.h"

namespace Mn
{
	union ColliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	class Scene;
	class CollisionManager
	{
	private:
		static WORD _Matrix[(UINT)eLayerType::Max];
		static std::map<UINT64, bool> _CollisionMap;
	public:
		static void Update();
		static void LayerCollision(Scene* scene,eLayerType left,eLayerType right);
		static void ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right);
		static bool Intersect(Collider* left, Collider* right);

		static void SetLayer(eLayerType left, eLayerType right, bool value);
		static void Clear();
	};
}
