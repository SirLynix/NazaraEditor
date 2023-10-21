#pragma once

#include <NazaraEditor/Core/Application/Action.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorAction_Log_Clear final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Log_Clear, false);

	public:
		void Execute() override;
	};

	class NAZARAEDITOR_CORE_API EditorAction_Log_CopyToClipboard final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Log_CopyToClipboard, false);

	public:
		void Execute() override;
	};
}