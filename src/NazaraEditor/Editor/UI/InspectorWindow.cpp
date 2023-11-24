#include <NazaraEditor/Editor/UI/InspectorWindow.hpp>

#include <NazaraEditor/Editor/Application.hpp>

#include <NazaraEditor/Core/Reflection.hpp>
#include <NazaraEditor/Core/Reflection/Editor.hpp>

namespace NzEditor
{
	InspectorWindow::InspectorWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, "LOC_EDITOR_WINDOW_INSPECTOR_TITLE")
	{
		app->OnEntitySelected.Connect(this, &InspectorWindow::OnEntitySelected);
	}

	void InspectorWindow::OnEditorGUI()
	{
		if (!m_currentEntity)
			return;

		Nz::EditorPropertyInspector<Nz::EditorRenderer> enumerator;
		enumerator.AddPropertyNoWrapper(m_currentEntity, "", "");
	}

	void InspectorWindow::OnEntitySelected(entt::handle entity)
	{
		m_currentEntity = entity;
	}

	void InspectorWindow::OnEntityDeselected(entt::handle)
	{
		m_currentEntity = {};
	}
}