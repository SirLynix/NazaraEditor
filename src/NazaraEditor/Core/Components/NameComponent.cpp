#include <NazaraEditor/Core/Components/NameComponent.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

#include <Nazara/Core/FilesystemAppComponent.hpp>
#include <Nazara/Core/Components/NodeComponent.hpp>
#include <Nazara/Graphics/Billboard.hpp>
#include <Nazara/Graphics/FramePipeline.hpp>
#include <Nazara/Graphics/MaterialInstance.hpp>
#include <Nazara/Graphics/TextureAsset.hpp>
#include <Nazara/Graphics/Systems/RenderSystem.hpp>

namespace Nz
{
	void EditorNameComponent::Update(Time, NodeComponent& node)
	{
		if (!m_icon.has_value())
			return;
		m_icon.value().instance->UpdateWorldMatrix(node.GetTransformMatrix());
	}

	void EditorNameComponent::SetIcon(const std::filesystem::path& path)
	{
		auto& level = EditorBaseApplication::Instance()->GetLevel();
		auto& renderer = level.GetEnttWorld()->GetSystem<RenderSystem>();

		if (m_icon.has_value())
		{
			renderer.GetFramePipeline().UnregisterRenderable(m_icon.value().index);
			m_icon = {};
		}

		auto& fs = EditorBaseApplication::Instance()->GetComponent<Nz::FilesystemAppComponent>();

		std::shared_ptr<Nz::TextureAsset> tex = fs.Open<Nz::TextureAsset>(path.string(), { .sRGB = true });
		std::shared_ptr<Nz::MaterialInstance> mat = Nz::MaterialInstance::GetDefault(Nz::MaterialType::Basic, Nz::MaterialInstancePreset::Transparent)->Clone();

		mat->SetTextureProperty("BaseColorMap", tex);
		mat->SetValueProperty("Billboard", true);

		m_icon = BillboardData{
			.index = 0,
			.instance = std::make_shared<Nz::WorldInstance>(),
			.billboard = std::make_shared<Nz::Billboard>(mat, Nz::Vector2f(1.f, 1.f))
		};

		auto& icon = m_icon.value();

		Nz::Recti scissorBox(-1, -1, -1, -1);

		Nz::ElementRendererRegistry elementRegistry;
		icon.index = renderer.GetFramePipeline().RegisterWorldInstance(icon.instance);
		renderer.GetFramePipeline().RegisterRenderable(icon.index, Nz::FramePipeline::NoSkeletonInstance, icon.billboard.get(), 0xFFFFFFFF, scissorBox);

		OnIconChanged(this, path);
	}
}