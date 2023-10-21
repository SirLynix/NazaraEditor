#include <NazaraEditor/Editor/Application.hpp>

#include <NazaraLocalization/Localization.hpp>

namespace NzEditor
{
	Application::Application()
	{
		Nz::Localization::OnLocaleInstalled.Connect([this](std::string_view locale) {
			RegisterAction<Nz::EditorAction_SetLocale>({
				.className = std::format("{}_{}", Nz::EditorAction_SetLocale::GetClassName(), locale),
				.description = locale,
				.path = { "LOC_EDITOR_MENU_TOOLS", "LOC_EDITOR_MENU_LANGUAGE", locale },
				.category = "Tools",
			}, locale);
		});
	}

	bool Application::NewLevel()
	{
		bool bResult = EditorBaseApplication::NewLevel();
		if (!bResult)
			return false;

		{
			auto directional = CreateEntity("SunLight");
			Nz::LightComponent& lightComponent = directional.emplace<Nz::LightComponent>();
			Nz::DirectionalLight& light = lightComponent.AddLight<Nz::DirectionalLight>();
			light.UpdateRotation(Nz::EulerAnglesf(-45.f, 0.f, 0.f));
		}
		{
			auto cube = CreateEntity("Cube");
			Nz::GraphicsComponent& graphicsComponent = cube.emplace<Nz::GraphicsComponent>();

			std::shared_ptr<Nz::GraphicalMesh> boxMesh = Nz::GraphicalMesh::Build(Nz::Primitive::Box(Nz::Vector3f(4.f), Nz::Vector3ui::Zero(), Nz::Matrix4f::Scale(Nz::Vector3f(-1.f)), Nz::Rectf(0.f, 0.f, 2.f, 2.f)));

			std::shared_ptr<Nz::MaterialInstance> boxMat = Nz::MaterialInstance::Instantiate(Nz::MaterialType::Phong);
			boxMat->DisablePass("ShadowPass");
			boxMat->UpdatePassesStates([&](Nz::RenderStates& states)
			{
				states.frontFace = Nz::FrontFace::Clockwise;
			});
			std::shared_ptr<Nz::Model> boxModel = std::make_shared<Nz::Model>(std::move(boxMesh));
			boxModel->SetMaterial(0, std::move(boxMat));
			graphicsComponent.AttachRenderable(boxModel);
		}
		return true;
	}
}