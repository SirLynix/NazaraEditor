#pragma once

#include <NazaraEditor/Core.hpp>

namespace NzEditor
{
	class Application
		: public Nz::EditorBaseApplication
	{
	public:
		virtual bool NewLevel() override;
	};
}