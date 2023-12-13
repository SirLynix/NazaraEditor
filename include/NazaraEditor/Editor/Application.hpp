#pragma once

#include <Nazara/Core/ApplicationComponent.hpp>

namespace Nz
{
	class EditorBaseApplication;
	class Level;
}

namespace NzEditor
{
	class Application
		: public Nz::ApplicationComponent
	{
	public:
		Application(Nz::ApplicationBase& app, Nz::EditorBaseApplication& editor);

	protected:
		void NewLevel(Nz::Level& level);

		Nz::EditorBaseApplication& m_editor;
	};
}