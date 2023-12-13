#include <NazaraEditor/Core/Application/ApplicationComponent.hpp>

#include <Nazara/Platform/Window.hpp>
#include <NazaraImgui/NazaraImgui.hpp>

namespace Nz
{
	EditorApplicationComponent::EditorApplicationComponent(ApplicationBase& app)
		: ApplicationComponent(app)
	{

	}

	void EditorApplicationComponent::Update(Time elapsedTime)
	{
		if (!GetWindow() || !GetWindow()->IsOpen())
			return;

		GetWindow()->ProcessEvents();

		GetPopupManager().Update();

		Nz::Imgui::Instance()->Update(elapsedTime.AsSeconds());
		Nz::Imgui::Instance()->Render();
	}
}