#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/Components/CameraComponent.hpp>
#include <NazaraEditor/Core/Components/NameComponent.hpp>
#include <NazaraEditor/Core/Systems/CameraSystem.hpp>

#include <Nazara/Core/AppEntitySystemComponent.hpp>
#include <Nazara/Graphics/Components/CameraComponent.hpp>
#include <Nazara/Graphics/FramePipeline.hpp>
#include <Nazara/Graphics/RenderTexture.hpp>
#include <Nazara/Graphics/RenderWindow.hpp>
#include <Nazara/Graphics/Systems/RenderSystem.hpp>
#include <Nazara/Platform/AppWindowingComponent.hpp>
#include <Nazara/Utility/Components/NodeComponent.hpp>

namespace Nz
{
	EditorBaseApplication* EditorBaseApplication::s_instance = nullptr;

	EditorBaseApplication::EditorBaseApplication()
		: m_level(this)
	{
		NazaraAssert(s_instance == nullptr, "EditorBaseApplication already exists");
		s_instance = this;


		std::filesystem::path resourceDir = "assets/editor";
		if (!std::filesystem::is_directory(resourceDir) && std::filesystem::is_directory("../.." / resourceDir))
			resourceDir = "../.." / resourceDir;
		SetResourceFolder(resourceDir);

		auto& windowing = AddComponent<Nz::AppWindowingComponent>();

		std::shared_ptr<Nz::RenderDevice> device = Nz::Graphics::Instance()->GetRenderDevice();

		std::string windowTitle = "Nazara Editor";
		Nz::Window& window = windowing.CreateWindow(Nz::VideoMode(1280, 720, 32), windowTitle);
		m_windowSwapchain = std::make_unique<Nz::WindowSwapchain>(device, window);
		m_window = &window;

		// Allocate texture for engine rendering
		{
			Nz::TextureInfo screenTextureInfo = {
				.pixelFormat = Nz::PixelFormat::RGBA8,
				.type = Nz::ImageType::E2D,
				.usageFlags = Nz::TextureUsage::ColorAttachment | Nz::TextureUsage::ShaderSampling | Nz::TextureUsage::TransferDestination,
				.levelCount = 1,
				.height = 720,
				.width = 1280
			};

			std::size_t size = Nz::PixelFormatInfo::ComputeSize(screenTextureInfo.pixelFormat, screenTextureInfo.width, screenTextureInfo.height, screenTextureInfo.depth);

			std::vector<std::uint8_t> defaultScreen(size, 0xFF);
			m_engineTexture = device->InstantiateTexture(screenTextureInfo, defaultScreen.data(), false);
		}

		// connect basic handler
		window.GetEventHandler().OnQuit.Connect([&window](const auto* handler) {
			NazaraUnused(handler);
			window.Close();
		});

		AddComponent<Nz::AppEntitySystemComponent>();

		Nz::Imgui::Instance()->Init(window);
		ImGui::EnsureContextOnThisThread();

		// load the passes after Imgui is init
		auto passList = Nz::PipelinePassList::LoadFromFile(m_resourceFolder / "editor.passlist");
		m_editorCamera = std::make_unique<Nz::Camera>(std::make_shared<RenderWindow>(*m_windowSwapchain), passList);

		AddUpdaterFunc(Interval{ Nz::Time::Milliseconds(16) }, [&](Nz::Time elapsed) {
			if (!window.IsOpen())
				return;

			window.ProcessEvents();

			m_popupManager.Update();

			Nz::Imgui::Instance()->Update(elapsed.AsSeconds());
			Nz::Imgui::Instance()->Render();

			//Nz::RenderFrame frame = m_windowSwapchain->AcquireFrame();
			//if (!frame)
			//	return;

			//Nz::Imgui::Instance()->Render(m_windowSwapchain->GetSwapchain(), frame);

			//frame.Present();
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
			RenderSystem& system = m_level.GetEnttWorld()->AddSystem<RenderSystem>();
			m_level.GetEnttWorld()->AddSystem<EditorCameraSystem>();

			system.AttachExternalSwapchain(*m_windowSwapchain);
			system.GetFramePipeline().RegisterViewer(m_editorCamera.get(), 2);

			// configure camera
			m_mainCamera = CreateEntity("MainCamera");
			auto& cmp = m_mainCamera.get<Nz::EditorNameComponent>();
			cmp.SetFlags(EditorEntityFlags_Hidden);

			auto passList = Nz::PipelinePassList::LoadFromFile(m_resourceFolder / "engine.passlist");
			
			auto& cameraComponent = m_mainCamera.emplace<Nz::CameraComponent>(std::make_shared<Nz::RenderTexture>(m_engineTexture), passList, Nz::ProjectionType::Perspective);
			cameraComponent.UpdateFOV(70.f);
			cameraComponent.UpdateClearColor(Nz::Color(0.46f, 0.48f, 0.84f, 1.f));

			m_mainCamera.emplace<Nz::EditorCameraComponent>(cameraComponent, system.GetFramePipeline().GetDebugDrawer());

			OnLevelChanged(m_level);
		}
		return bRes;
	}
}