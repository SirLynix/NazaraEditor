#pragma once

#include <NazaraEditor/Core/Application/Action.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorAction_Level_New final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Level_New, false);

	public:
		void Execute() override;
	};

	class NAZARAEDITOR_CORE_API EditorAction_Level_Open final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Level_Open, false);

	public:
		void Execute() override;
	};

	class NAZARAEDITOR_CORE_API EditorAction_Level_Save final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Level_Save, false);

	public:
		void Execute() override;
	};
}