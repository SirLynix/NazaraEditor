#pragma once

#include <Nazara/Core/ResourceManager.hpp>

#include <string>

namespace Nz
{
	class Asset
	{
	public:
		virtual bool IsExtensionSupported(std::string_view ext) = 0;
	};

	template<typename TResourceManager>
	class TAsset
	{
	public:
		virtual bool IsExtensionSupported(std::string_view ext) { return m_resourceManager. }
	protected:
		TResourceManager m_resourceManager;
	};
}