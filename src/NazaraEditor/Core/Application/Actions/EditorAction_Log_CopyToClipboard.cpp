#include <NazaraEditor/Core/Application/Actions/EditorAction_Log_CopyToClipboard.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/Application/EditorLogger.hpp>

#include <Nazara/Platform.hpp>

#include <sstream>

namespace Nz
{
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