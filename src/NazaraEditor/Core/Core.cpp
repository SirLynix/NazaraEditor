#include <NazaraEditor/Core/Core.hpp>

namespace Nz
{
	EditorCore* EditorCore::s_instance = nullptr;

	EditorCore::EditorCore(Config /*config*/)
		: ModuleBase("EditorCore", this)
	{
		ImGui::EnsureContextOnThisThread();
	}

	EditorCore::~EditorCore() {}
}