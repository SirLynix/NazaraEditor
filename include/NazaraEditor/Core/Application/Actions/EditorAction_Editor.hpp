#pragma once

#include <NazaraEditor/Core/Application/Action.hpp>

namespace Nz
{
	NAZARAEDITOR_CORE_API void RegisterEditorActions(class EditorBaseApplication& app);

	class NAZARAEDITOR_CORE_API EditorAction_Quit final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Quit, false);

	public:
		void Execute() override;
	};

	class NAZARAEDITOR_CORE_API EditorAction_SetLocale final
		: public EditorAction
	{
	public:
		EditorAction_SetLocale(const Properties& properties, std::string_view locale)
		: EditorAction(properties)
			, m_locale(locale)
		{}
		EditorAction_SetLocale(const std::shared_ptr<Properties>& properties, std::string_view locale)
		: EditorAction(properties)
			, m_locale(locale)
		{}
		~EditorAction_SetLocale() = default;

		std::unique_ptr<EditorAction> Clone() const override { return std::make_unique<EditorAction_SetLocale>(m_properties, m_locale); }
		const std::string& GetName() const override { return m_properties->className; }
		bool IsUndoRedoable() const override { return false; }
		static const char* GetClassName() { return "EditorAction_SetLocale"; }

		void Execute() override;

	protected:
		std::string m_locale;
	};
}