#pragma once

#include <NazaraEditor/Core/Config.hpp>
#include <NazaraEditor/Core/Application/Shortcut.hpp>

#include <NazaraLocalization/LocalizedText.hpp>

#include <memory>
#include <string>

namespace Nz
{
	class Texture;

	class NAZARAEDITOR_CORE_API EditorAction
	{
	public:
		struct Properties
		{
			std::string className;
			Nz::LocalizedText description;
			std::vector<Nz::LocalizedText> path;
			std::string category;
			Nz::Shortcut shortcut;

			std::shared_ptr<Nz::Texture> icon;
		};

		EditorAction(const Properties& properties)
			: m_properties(std::make_shared<Properties>(properties))
		{}
		EditorAction(const std::shared_ptr<Properties>&properties)
			: m_properties(properties)
		{}
		virtual ~EditorAction() = default;

		EditorAction(const EditorAction&) = delete;
		EditorAction& operator=(const EditorAction&) = delete;
		EditorAction(EditorAction&&) = delete;
		EditorAction& operator=(EditorAction&&) = delete;

		virtual std::unique_ptr<EditorAction> Clone() const = 0;
		virtual const std::string& GetName() const = 0;
		virtual bool IsUndoRedoable() const = 0;
		static const char* GetClassName() { return "EditorAction"; }

		virtual void Execute() {};
		virtual void Revert() {};

		template <typename TAction>
		TAction* As() { return static_cast<TAction*>(this); }

		template <typename TAction>
		const TAction* As() const { return static_cast<const TAction*>(this); }

	protected:
		std::shared_ptr<Properties> m_properties;
	};

#define EDITORACTION_BODY(Typename, bUndoRedoable) \
	public: \
		Typename(const Properties& properties) \
			: EditorAction(properties) \
		{} \
		Typename(const std::shared_ptr<Properties>& properties) \
			: EditorAction(properties) \
		{} \
		~Typename() = default; \
		std::unique_ptr<EditorAction> Clone() const override { return std::make_unique<Typename>(m_properties); } \
		const std::string& GetName() const override { return m_properties->className; } \
		bool IsUndoRedoable() const override { return bUndoRedoable; } \
		static const char* GetClassName() { return #Typename; }
}