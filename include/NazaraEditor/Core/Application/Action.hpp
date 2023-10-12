#pragma once

#include <NazaraEditor/Core/Core.hpp>

#include <NazaraEditor/Core/Application/Shortcut.hpp>

#include <Nazara/Renderer.hpp>

#include <string>

namespace Nz
{
	class EditorAction
	{
	public:
		struct Properties
		{
			std::string name;
			std::string description;
			Nz::Shortcut shortcut;

			Nz::Texture* icon;
		};

		EditorAction(const Properties& properties)
			: m_properties(std::make_shared<Properties>(properties))
		{}
		virtual ~EditorAction() = default;

		EditorAction(const EditorAction&) = delete;
		EditorAction& operator=(const EditorAction&) = delete;
		EditorAction(EditorAction&&) = delete;
		EditorAction& operator=(EditorAction&&) = delete;

		virtual void Execute() = 0;
		virtual void Revert() = 0;
		virtual EditorAction* Clone() const = 0;

	protected:
		EditorAction(const std::shared_ptr<Properties>& properties)
			: m_properties(properties)
		{}

		std::shared_ptr<Properties> m_properties;
	};
}