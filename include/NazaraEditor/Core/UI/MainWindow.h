#pragma once

#include <NazaraEditor/Core/UI/Window.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorMainWindow
		: public EditorWindow
	{
	public:
		EditorMainWindow(EditorBaseApplication* app, const std::string& name = "");
		virtual ~EditorMainWindow() = default;

	protected:
		virtual void OnRenderImgui() override;
	};
}