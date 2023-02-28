#pragma once
#include "MnEngine.h"

namespace Mn {
	class Entity
	{
	private:
		std::wstring _Name;

	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { _Name = name; }
		std::wstring& GetName() { return _Name; }
	};
}



