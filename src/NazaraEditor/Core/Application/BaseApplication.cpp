#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	EditorBaseApplication::EditorBaseApplication()
		: m_level(this)
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

		NewLevel();

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

	Nz::Level& EditorBaseApplication::GetLevel()
	{
		return m_level;
	}

	entt::handle EditorBaseApplication::CreateEntity()
	{
		entt::handle entity = m_level.CreateEntity();
		entity.emplace<Nz::NodeComponent>();

		OnEntityCreated(entity);
		OnEntitySelected(entity);
		return entity;
	}

	bool EditorBaseApplication::NewLevel()
	{
		bool bRes = m_level.CreateNewLevel();
		if (bRes)
		{
			OnLevelChanged(m_level);
		}
		return bRes;
	}
}