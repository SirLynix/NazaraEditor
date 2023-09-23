#include <NazaraEditor/Core/UI/Window.hpp>

#include <Nazara/Core/StringExt.hpp>

namespace Nz
{
	EditorWindow::EditorWindow(const std::string& name)
		: m_windowName(name)
	{
		Nz::Imgui::Instance()->AddHandler(this);
	}

	EditorWindow::~EditorWindow()
	{
		Nz::Imgui::Instance()->RemoveHandler(this);
	}

	void EditorWindow::OnRenderImgui()
	{
		bool bNeedsMenu = !m_root.entries.empty();
		ImGuiWindowFlags flags = (bNeedsMenu ? ImGuiWindowFlags_MenuBar : 0);

		if (ImGui::Begin(m_windowName.c_str(), nullptr, flags))
		{
			DrawMenus();

			OnEditorGUI();

			ImGui::End();
		}
	}

	void EditorWindow::AddMenuAction(const std::string& path, const std::string& shortcut, ActionCallback callback)
	{
		std::vector<std::string_view> v;
		Nz::SplitString(path, "|", [&](std::string_view str) { v.push_back(str); return true; });

		std::string leaf = std::string(v.back());

		v.pop_back(); // remove action name from hierarchy

		MenuList& parent = GetOrCreateMenuHierarchy(v);

		parent.entries.push_back(MenuAction{ leaf, shortcut, callback});
	}

	void EditorWindow::AddMenuSeparator(const std::string& path)
	{
		std::vector<std::string_view> v;
		Nz::SplitString(path, "|", [&](std::string_view str) { v.push_back(str); return true; });
		MenuList& parent = GetOrCreateMenuHierarchy(v);
		parent.entries.push_back(MenuSeparator{});
	}

	void EditorWindow::DrawMenus()
	{
		if (m_root.entries.empty())
			return;

		std::function<void(const std::variant<MenuAction, MenuSeparator, MenuList>&)> visitor;
		
		visitor = [&visitor](auto& menu) {
			std::visit(Overloaded{
				[&visitor](const MenuList& arg) {
					if (ImGui::BeginMenu(arg.label.c_str()))
					{
						for (auto& child : arg.entries)
							visitor(child);
						ImGui::EndMenu();
					}
				},
				[](const MenuSeparator&) {
					ImGui::Separator();
				},
				[](const MenuAction& arg) {
					if (ImGui::MenuItem(arg.label.c_str(), arg.shortcut.c_str()))
						arg.callback();
				},
				}, menu);
		};

		if (ImGui::BeginMenuBar())
		{
			for (auto& menu : m_root.entries)
				visitor(menu);
			ImGui::EndMenuBar();
		}
	}

	EditorWindow::MenuList& EditorWindow::GetOrCreateMenuHierarchy(const std::vector<std::string_view>& hierarchy)
	{
		auto getOrCreate_submenu = [](MenuList* menu, std::string_view v) -> MenuList*
		{
			for (auto& e : menu->entries)
			{
				MenuList* ptr = nullptr;
				std::visit(Overloaded{
					[&ptr, v](MenuList& arg) { 
						if (arg.label == v)
							ptr = &arg;
					},
					[](MenuSeparator&) { },
					[](MenuAction&) { },
					}, e);
				if (nullptr != ptr)
					return ptr;
			}
			
			menu->entries.push_back(MenuList{ std::string(v) });
			return &std::get<MenuList>(menu->entries.back());
		};
		
		MenuList* currentMenu = &m_root;
		for (auto& entry : hierarchy)
			currentMenu = getOrCreate_submenu(currentMenu, entry);

		return *currentMenu;
	}
}