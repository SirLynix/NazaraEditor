#pragma once

#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <NazaraEditor/Core/Core.hpp>
#include <NazaraEditor/Core/Application/Action.hpp>
#include <NazaraEditor/Core/Application/ActionStack.hpp>
#include <NazaraEditor/Core/Application/EditorLogger.hpp>
#include <NazaraEditor/Core/Application/Level.hpp>
#include <NazaraEditor/Core/Asset/AssetManager.hpp>
#include <NazaraEditor/Core/UI/PopupManager.hpp>
#include <NazaraEditor/Core/UI/Window.hpp>
#include <NazaraImgui/NazaraImgui.hpp>
#include <NazaraLocalization/Localization.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorBaseApplication
		: public Nz::Application<Nz::Graphics, Nz::Imgui, Nz::Localization, Nz::EditorCore>
	{
	public:
		NazaraSignal(OnLevelChanged, Nz::Level&);

		// Entity lifetime events
		NazaraSignal(OnEntityCreated, entt::handle);
		NazaraSignal(OnEntityDestroyed, entt::handle);
		NazaraSignal(OnEntityParentChanged, entt::handle);

		// Entity selection events
		NazaraSignal(OnEntitySelected, entt::handle);
		NazaraSignal(OnEntityDeselected, entt::handle);

		// Editor events
		NazaraSignal(OnActionRegistered, const EditorAction::Properties&);

		EditorBaseApplication();
		virtual ~EditorBaseApplication();

		static EditorBaseApplication* Instance();
		
		ActionStack& GetActionStack() { return m_actionStack; }
		const ActionStack& GetActionStack() const { return m_actionStack; }
		EditorPopupManager& GetPopupManager() { return m_popupManager; }
		const EditorPopupManager& GetPopupManager() const { return m_popupManager; }
		EditorLogger& GetLogger() { return *m_logger; }
		const EditorLogger& GetLogger() const { return *m_logger; }
		AssetManager& GetAssetManager() { return m_assetManager; }
		const AssetManager& GetAssetManager() const { return m_assetManager; }

		void SetResourceFolder(const std::filesystem::path& path) { m_resourceFolder = path; }
		std::filesystem::path GetResourceFolder() const { return m_resourceFolder; }

		void SetLogger(EditorLogger& logger) { m_logger = &logger; }

		Nz::Level& GetLevel();
		virtual bool NewLevel();
		virtual bool CloseLevel() { return false; }
		virtual bool OpenLevel(const std::filesystem::path& /*path*/) { return false; }

		entt::handle CreateEntity(const std::string& name);

		template<typename T>
		void RegisterWindow()
		{
			static_assert(std::is_base_of<Nz::EditorWindow, T>::value, "Register Window should be called with a subclass of Nz::EditorWindow");
			m_windows.push_back(std::make_unique<T>(this));
		}

		template <typename TAction, typename... TArgs>
		void RegisterAction(EditorAction::Properties properties, TArgs&&... args)
		{
			if (properties.className.empty())
				properties.className = TAction::GetClassName();
			m_actionStack.RegisterAction<TAction>(properties, std::forward<TArgs...>(args)...);
			OnActionRegistered(properties);
		}

	private:
		static EditorBaseApplication* s_instance;

		std::unique_ptr<Nz::WindowSwapchain> m_windowSwapchain;
		std::vector<std::unique_ptr<Nz::EditorWindow>> m_windows;

		std::filesystem::path m_resourceFolder;
		Nz::ActionStack m_actionStack;
		Nz::AssetManager m_assetManager;
		Nz::EditorPopupManager m_popupManager;
		Nz::EditorLogger* m_logger;

		Nz::Level m_level;
	};
}