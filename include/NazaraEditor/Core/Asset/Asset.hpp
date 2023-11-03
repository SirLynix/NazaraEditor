#pragma once

#include <NazaraEditor/Core/Asset/AssetManager.hpp>
#include <NazaraUtils/TypeName.hpp>

#include <filesystem>
#include <memory>
#include <string_view>

namespace Nz
{
	template <typename TResource>
	class NAZARAEDITOR_CORE_API Asset
	{
	public:
		Asset() = default;
		Asset(const std::filesystem::path& path)
		{
			LoadAssetInternal(path);
		}

		~Asset() = default;

		Asset(const Asset&) noexcept = default;
		Asset(Asset&&) noexcept = default;
		Asset& operator=(const Asset&) = default;
		Asset& operator=(Asset&&) = default;

		inline bool IsValid() const { return !!m_resource; }
		inline bool operator()() const { return IsValid(); }

		inline operator std::shared_ptr<TResource>&() { return m_resource; }
		inline operator std::shared_ptr<TResource>() const { return m_resource; }

		inline static constexpr std::string_view GetAssetTypeName() { return Nz::TypeName<TResource>(); }
		inline const std::shared_ptr<TResource>& Get() const { return m_resource; }

	private:
		void LoadAssetInternal(const std::filesystem::path& path)
		{
			m_resource = AssetManager::Instance().LoadAsset<TResource>(path);
		}

		std::shared_ptr<TResource> m_resource;
	};
}