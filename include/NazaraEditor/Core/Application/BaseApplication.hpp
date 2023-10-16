#pragma once

#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <NazaraEditor/Core/Core.hpp>
#include <NazaraEditor/Core/Application/Action.hpp>
#include <NazaraEditor/Core/Application/ActionStack.hpp>
#include <NazaraEditor/Core/Application/Level.hpp>
#include <NazaraEditor/Core/UI/Window.hpp>
#include <NazaraImgui/NazaraImgui.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorBaseApplication
		: public Nz::Application<Nz::Graphics, Nz::Imgui, Nz::EditorCore>
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
		virtual ~EditorBaseApplication() = default;

		Nz::Level& GetLevel();
		bool NewLevel();
		bool CloseLevel();
		bool OpenLevel(const std::filesystem::path& path);

		entt::handle CreateEntity(const std::string& name);

		template<typename T>
		void RegisterWindow()
		{
			static_assert(std::is_base_of<Nz::EditorWindow, T>::value, "Register Window should be called with a subclass of Nz::EditorWindow");
			m_windows.push_back(std::make_unique<T>(this));
		}

		template <typename TAction>
		void RegisterAction(EditorAction::Properties properties)
		{
			properties.className = TAction::GetClassName();
			m_actionStack.RegisterAction<TAction>(properties);
			OnActionRegistered(properties);
		}

	private:
		std::unique_ptr<Nz::WindowSwapchain> m_windowSwapchain;
		std::vector<std::unique_ptr<Nz::EditorWindow>> m_windows;

		Nz::ActionStack m_actionStack;
		Nz::Level m_level;
	};
}