#pragma once
#include "Commoninclude.h"
#include "MnCollider.h"
#include "MnEnum.h"

namespace Mn
{
	class Scene;
	class CollisionManager
	{
	private:
		static WORD _Matrix[(UINT)eLayerType::Max];
	public:
		static void Update();
		static void LayerCollision(Scene* scene,eLayerType left,eLayerType right);
		static bool Intersect(Collider* left, Collider* right);

		static void SetLayer(eLayerType left, eLayerType right, bool value);
		static void Clear();
	};
}
