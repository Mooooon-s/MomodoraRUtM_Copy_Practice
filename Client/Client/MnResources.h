#pragma once
#include "MnResource.h"

namespace Mn {
	class Resources
	{
	private:
		static std::map<std::wstring, Resource*> _Resources;
	public:
		template<typename T>
		static T* Find(const std::wstring& key) {
			std::map<std::wstring,Resource*>::iterator iter = _Resources.find(key);
			if (iter != _Resources.end()) 
			{
				return dynamic_cast<T*>(iter->second);
			}

			return nullptr;
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->Key(key);
			resource->Path(path);
			_Resources.insert(std::make_pair(key, resource));

			return dynamic_cast <T*>(resource);

		}

		static void Release()
		{
			for (auto resouse : _Resources)
			{
				delete resouse.second;
				resouse.second = nullptr;
			}

		}

	};
}

