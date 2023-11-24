#pragma once

#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace NzEditor
{
	class Application
		: public Nz::EditorBaseApplication
	{
	public:
		Application();

		virtual bool NewLevel() override;
	};
}