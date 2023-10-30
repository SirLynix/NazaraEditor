#include <NazaraEditor/Core/Application/Actions/EditorAction_Log.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	void RegisterLogActions(EditorBaseApplication& app)
	{
		app.RegisterAction<Nz::EditorAction_Log_Clear>({
				.description = "LOC_EDITOR_ACTION_LOG_CLEAR_DESC",
				.path = { "LOC_EDITOR_MENU_LOG_CLEAR" },
				.category = "Output",
			});
		app.RegisterAction<Nz::EditorAction_Log_CopyToClipboard>({
				.description = "LOC_EDITOR_ACTION_LOG_COPY_DESC",
				.path = { "LOC_EDITOR_MENU_LOG_COPY" },
				.category = "Output",
			});
	}

	void EditorAction_Log_Clear::Execute()
	{
		Nz::EditorBaseApplication::Instance()->GetLogger().Clear();
	}

	void EditorAction_Log_CopyToClipboard::Execute()
	{
		auto& lines = Nz::EditorBaseApplication::Instance()->GetLogger().GetLog();
		if (lines.empty())
			return;

		std::ostringstream oss;
		oss << lines[0];
		for (size_t i = 1; i < lines.size(); ++i)
			oss << '\n' << lines[i];

		Nz::Clipboard::SetString(oss.str());
	}
}