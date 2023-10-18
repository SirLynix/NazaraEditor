#include <NazaraEditor/Editor/UI/OutputWindow.hpp>

#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/Application/EditorLogger.hpp>

namespace NzEditor
{
	OutputWindow::OutputWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, "Output", { "Output" })
		, m_bScrollToBottom(true)
		, m_bScrollToTop(false)
	{
	}

	void OutputWindow::OnEditorGUI()
	{
		if (ImGui::BeginChild("scrolling"))
		{
			for (auto&& line : Nz::EditorBaseApplication::Instance()->GetLogger().GetLog())
				ImGui::TextUnformatted(line.c_str());

			if (m_bScrollToBottom)
			{
				ImGui::SetScrollHereY(1.0f);
				m_bScrollToBottom = false;
			}
			if (m_bScrollToTop)
			{
				ImGui::SetScrollHereY(0.f);
				m_bScrollToTop = false;
			}
			ImGui::EndChild();
		}
	}
}