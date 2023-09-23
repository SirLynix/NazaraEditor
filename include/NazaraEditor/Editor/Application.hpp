#pragma once

#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <NazaraEditor/Core.hpp>
#include <NazaraImgui/NazaraImgui.hpp>

namespace Nz
{
	class EditorApplication
		: public Nz::Application<Nz::Graphics, Nz::Imgui, Nz::EditorCore>
	{
	public:
		NazaraSignal(OnWorldChanged, Nz::EnttWorld*);

		// Entity lifetime events
		NazaraSignal(OnEntityCreated, entt::handle);
		NazaraSignal(OnEntityDestroyed, entt::handle);
		NazaraSignal(OnEntityParentChanged, entt::handle);

		// Entity selection events
		NazaraSignal(OnEntitySelected, entt::handle);
		NazaraSignal(OnEntityDeselected, entt::handle);

		static EditorApplication& Instance();

		void NewWorld();
		Nz::EnttWorld* GetCurrentWorld();

		entt::handle CreateEntity();

		template<typename T>
		void RegisterWindow() 
		{
			static_assert(std::is_base_of<Nz::EditorWindow, T>::value, "Register Window should be called with a subclass of Nz::EditorWindow");
			m_windows.push_back(std::make_unique<T>());
		}

	private:
		EditorApplication();

		std::unique_ptr<Nz::WindowSwapchain> m_windowSwapchain;
		Nz::EnttWorld* m_world;

		std::vector<std::unique_ptr<Nz::EditorWindow>> m_windows;
	};
}