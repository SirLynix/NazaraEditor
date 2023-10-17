#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/Components/NameComponent.hpp>

namespace Nz
{
	EditorBaseApplication* EditorBaseApplication::s_instance = nullptr;

	EditorBaseApplication::EditorBaseApplication()
		: m_level(this)
	{
		NazaraAssert(s_instance == nullptr, "EditorBaseApplication already exists");
		s_instance = this;

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

	EditorBaseApplication::~EditorBaseApplication()
	{
		s_instance = nullptr;
	}

	EditorBaseApplication* EditorBaseApplication::Instance()
	{
		return s_instance;
	}

	Nz::Level& EditorBaseApplication::GetLevel()
	{
		return m_level;
	}

	entt::handle EditorBaseApplication::CreateEntity(const std::string& name)
	{
		entt::handle entity = m_level.CreateEntity();
		Nz::EditorNameComponent& nameComponent = entity.emplace<Nz::EditorNameComponent>();
		nameComponent.SetName(name);

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
			// configure camera
			auto camera = CreateEntity("Camera");
			auto& cmp = camera.get<Nz::EditorNameComponent>();
			//cmp.SetFlags(EditorEntityFlags_Hidden);
			
			auto& cameraComponent = camera.emplace<Nz::CameraComponent>(m_windowSwapchain.get(), Nz::ProjectionType::Perspective);
			cameraComponent.UpdateFOV(70.f);
			cameraComponent.UpdateClearColor(Nz::Color(0.46f, 0.48f, 0.84f, 1.f));

			OnLevelChanged(m_level);
		}
		return bRes;
	}
}