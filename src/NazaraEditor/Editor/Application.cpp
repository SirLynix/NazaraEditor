#include <NazaraEditor/Editor/Application.hpp>

namespace Nz
{
	EditorApplication::EditorApplication()
		: m_world(nullptr)
	{
		auto& windowing = AddComponent<Nz::AppWindowingComponent>();

		std::shared_ptr<Nz::RenderDevice> device = Nz::Graphics::Instance()->GetRenderDevice();

		std::string windowTitle = "Nazara Editor";
		Nz::Window& window = windowing.CreateWindow(Nz::VideoMode(1280, 720, 32), windowTitle);
		m_windowSwapchain = std::make_unique<Nz::WindowSwapchain>(device, window);

		// connect basic handler
		window.GetEventHandler().OnQuit.Connect([&window](const auto* handler) {
			NazaraUnused(handler);
			window.Close();
		});

		AddComponent<Nz::AppEntitySystemComponent>();

		Nz::Imgui::Instance()->Init(window);
		ImGui::EnsureContextOnThisThread();

		NewWorld();

		AddUpdaterFunc(Interval{ Nz::Time::Milliseconds(16) }, [&](Nz::Time elapsed) {
			if (!window.IsOpen())
				return;

			window.ProcessEvents();

			Nz::RenderFrame frame = m_windowSwapchain->AcquireFrame();
			if (!frame)
				return;

			Nz::Imgui::Instance()->Update(window, elapsed.AsSeconds());

			Nz::Imgui::Instance()->Render(m_windowSwapchain.get(), frame);

			frame.Present();
		});
	}

	EditorApplication& EditorApplication::Instance()
	{
		static EditorApplication e;
		return e;
	}

	Nz::EnttWorld* EditorApplication::GetCurrentWorld()
	{
		return m_world;
	}

	entt::handle EditorApplication::CreateEntity()
	{
		if (m_world == nullptr)
			return {};

		entt::handle entity = m_world->CreateEntity();
		entity.emplace<Nz::NodeComponent>();

		OnEntityCreated(entity);
		OnEntitySelected(entity);
		return entity;
	}

	void EditorApplication::NewWorld()
	{
		auto& ecs = GetComponent<Nz::AppEntitySystemComponent>();
		m_world = &ecs.AddWorld<Nz::EnttWorld>();
	}
}