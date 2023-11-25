#pragma once

#include <NazaraEditor/Core/Application/Action.hpp>

#include <Nazara/Math/Vector2.hpp>

namespace Nz
{
	NAZARAEDITOR_CORE_API void RegisterCameraActions(class EditorBaseApplication& app);

	class NAZARAEDITOR_CORE_API EditorAction_SetCameraSize final
		: public EditorAction
	{
	public:
		EditorAction_SetCameraSize(const Properties& properties, const Nz::Vector2ui& size)
			: EditorAction(properties)
			, m_size(size)
		{}
		EditorAction_SetCameraSize(const std::shared_ptr<Properties>& properties, const Nz::Vector2ui& size)
			: EditorAction(properties)
			, m_size(size)
		{}
		~EditorAction_SetCameraSize() = default;

		std::unique_ptr<EditorAction> Clone() const override { return std::make_unique<EditorAction_SetCameraSize>(m_properties, m_size); }
		const std::string& GetName() const override { return m_properties->className; }
		bool IsUndoRedoable() const override { return false; }
		static const char* GetClassName() { return "EditorAction_SetCameraSize"; }

		void Execute() override;

	protected:
		Nz::Vector2ui m_size;
	};

	class NAZARAEDITOR_CORE_API EditorAction_SetCameraStretchMode final
		: public EditorAction
	{
	public:
		EditorAction_SetCameraStretchMode(const Properties& properties, StretchMode mode)
			: EditorAction(properties)
			, m_mode(mode)
		{}
		EditorAction_SetCameraStretchMode(const std::shared_ptr<Properties>& properties, StretchMode mode)
			: EditorAction(properties)
			, m_mode(mode)
		{}
		~EditorAction_SetCameraStretchMode() = default;

		std::unique_ptr<EditorAction> Clone() const override { return std::make_unique<EditorAction_SetCameraStretchMode>(m_properties, m_mode); }
		const std::string& GetName() const override { return m_properties->className; }
		bool IsUndoRedoable() const override { return false; }
		static const char* GetClassName() { return "EditorAction_SetCameraStretchMode"; }

		void Execute() override;

	protected:
		StretchMode m_mode;
	};
}