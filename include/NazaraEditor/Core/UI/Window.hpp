#pragma once

#include <NazaraUtils/Prerequisites.hpp>
#include <NazaraEditor/Core/Config.hpp>
#include <NazaraImgui/NazaraImgui.hpp>

namespace Nz
{
	using ActionCallback = std::function<void(void)>;

	class EditorBaseApplication;

	class NAZARAEDITOR_CORE_API EditorWindow
		: private Nz::ImguiHandler
	{
	public:
		EditorWindow(EditorBaseApplication* app, const std::string& name = "");
		~EditorWindow();

		EditorWindow(const EditorWindow&) = delete;
		EditorWindow& operator=(const EditorWindow&) = delete;

		virtual void OnRenderImgui() override;

		void AddMenuAction(const std::string& path, const std::string& shortcut, ActionCallback callback);
		void AddMenuSeparator(const std::string& path);

	protected:
		virtual void OnEditorGUI() {};

	private:
		void DrawMenus();

		EditorBaseApplication* m_application;
		std::string m_windowName;

		struct MenuAction
		{
			std::string label;
			std::string shortcut;
			ActionCallback callback;
		};

		struct MenuSeparator
		{};

		struct MenuList
		{
			std::string label;
			std::vector<std::variant<MenuAction, MenuSeparator, MenuList>> entries;
		};

		MenuList m_root;

		MenuList& GetOrCreateMenuHierarchy(const std::vector<std::string_view>& hierarchy);
	};
}