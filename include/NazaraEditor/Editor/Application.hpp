#pragma once

#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace NzEditor
{
	class Application
		: public Nz::EditorBaseApplication
	{
	public:
		Application(int argc, char** argv);

		virtual bool NewLevel() override;
	};
}