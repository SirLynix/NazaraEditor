#include <NazaraEditor/Core/Asset/AssetManager.hpp>

namespace Nz
{
	AssetManager* AssetManager::s_instance = nullptr;

	AssetManager::AssetManager()
	{
		NazaraAssert(s_instance == nullptr, "AssetManager already instanced");
		s_instance = this;
	}

	AssetManager::~AssetManager()
	{
		s_instance = nullptr;
	}

	AssetManager& AssetManager::Instance()
	{
		return *s_instance;
	}
}