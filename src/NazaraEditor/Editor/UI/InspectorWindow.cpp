#include <NazaraEditor/Editor/UI/InspectorWindow.hpp>

#include <NazaraEditor/Editor/Application.hpp>

namespace Nz
{
	EditorInspectorWindow::EditorInspectorWindow()
		: Nz::EditorWindow("Inspector")
	{
		EditorApplication::Instance().OnEntitySelected.Connect(this, &EditorInspectorWindow::OnEntitySelected);
	}

	void EditorInspectorWindow::OnEditorGUI()
	{
		if (!m_currentEntity)
			return;

		Nz::EditorPropertyInspector<Nz::EditorRenderer> enumerator;
		enumerator.AddProperty(m_currentEntity, "", "");
		ImGui::End();
	}

	void EditorInspectorWindow::OnEntitySelected(entt::handle entity)
	{
		m_currentEntity = entity;
	}

	void EditorInspectorWindow::OnEntityDeselected(entt::handle)
	{
		m_currentEntity = {};
	}
}