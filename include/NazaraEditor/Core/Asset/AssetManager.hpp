#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/ResourceLoader.hpp>

#include <nlohmann/json.hpp>

#include <unordered_map>
#include <typeindex>

namespace Nz
{
	template <typename TResource>
	class NAZARAEDITOR_CORE_API AssetDescriptor
	{
	public:
		bool LoadFromFile(const std::filesystem::path& path)
		{
			using namespace nlohmann;

			std::ifstream file(path);
			auto data = json::parse(file);

			if (data.find("type") == data.end())
				return false;

			type = data["type"].get<std::string>();
			if (type != TypeName<TResource>())
				return false;

			if (data.find("path") == data.end())
				return false;

			assetPath = data["path"].get<std::string>();
			return true;
		}

		std::string type;
		std::filesystem::path assetPath;
		TResource::Params parameters;
	};

	class NAZARAEDITOR_CORE_API IAssetLoader {
	public:
		virtual ~IAssetLoader() = default;
	};

	template <typename TResource>
	class NAZARAEDITOR_CORE_API AssetLoader
		: public IAssetLoader
	{
	public:
		inline static constexpr std::string_view GetAssetTypeName() { return TypeName<TResource>(); }

		std::shared_ptr<TResource> LoadAsset(const std::filesystem::path& path)
		{
			AssetDescriptor<TResource> descriptor;
			if (!descriptor.LoadFromFile(path))
				return {};

			return m_loader.LoadFromFile(descriptor.assetPath, descriptor.parameters);
		}

	private:
		using TResourceParams = TResource::Params;
		ResourceLoader<TResource, TResourceParams> m_loader;
	};

	class NAZARAEDITOR_CORE_API AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		AssetManager(const AssetManager&) = delete;
		AssetManager(AssetManager&&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		AssetManager& operator=(AssetManager&&) = delete;

		static AssetManager& Instance();

		template <typename TResource>
		std::shared_ptr<TResource> LoadAsset(const std::filesystem::path& path)
		{
			auto it = m_loaders.find(typeid(TResource));
			if (it == m_loaders.end())
				return {};

			AssetLoader<TResource>* loader = static_cast<AssetLoader<TResource>*>(it->second.get());
			return loader->LoadAsset(path);
		}

		template <typename TResource>
		void RegisterLoader()
		{
			m_loaders[typeid(TResource)] = std::make_unique<AssetLoader<TResource>>();
		}

	private:
		std::unordered_map<std::type_index, std::unique_ptr<IAssetLoader>> m_loaders;

		static AssetManager* s_instance;
	};
}