#include <NazaraEditor/Core/UI/Window.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

#include <Nazara/Core/StringExt.hpp>
#include <NazaraImgui/NazaraImgui.hpp>

namespace Nz
{
	EditorWindow::EditorWindow(EditorBaseApplication* app, const Nz::LocalizedText& name, const std::vector<std::string>& categories)
		: m_application(app)
		, m_windowName(name)
		, m_categories(categories)
	{
		Nz::Imgui::Instance()->AddHandler(this);

		// Automatically add actions to menus
		app->OnActionRegistered.Connect([this](auto&& prop) {
			if (!HasMenuCategory(prop.category))
				return;

			auto name = prop.className;
			AddMenuAction(prop.path, prop.shortcut.ToString(), [name]() { Nz::EditorBaseApplication::Instance()->GetActionStack().ExecuteAction(name); }, prop.icon);
		});
	}

	EditorWindow::~EditorWindow()
	{
		Nz::Imgui::Instance()->RemoveHandler(this);
	}

	void EditorWindow::OnRenderImgui()
	{
		bool bNeedsMenu = !m_root.entries.empty();
		ImGuiWindowFlags flags = (bNeedsMenu ? ImGuiWindowFlags_MenuBar : 0);

		// using name###ID form to ensure ID is consistent across translations
		std::string name = std::format("{}###{}", m_windowName.ToString(), m_windowName.GetBaseString());

		if (ImGui::Begin(name.c_str(), nullptr, flags))
		{
			if (ImGui::BeginMenuBar())
			{
				DrawMenus();
				ImGui::EndMenuBar();
			}

			OnEditorGUI();

			ImGui::End();
		}
	}

	void EditorWindow::AddMenuAction(const std::vector<Nz::LocalizedText>& path, const std::string& shortcut, ActionCallback callback, const std::shared_ptr<Nz::Texture>& icon)
	{
		std::vector<Nz::LocalizedText> copy = path;
		Nz::LocalizedText leaf = copy.back();

		copy.pop_back(); // remove action name from hierarchy

		MenuList& parent = GetOrCreateMenuHierarchy(copy);

		parent.entries.push_back(MenuAction{ leaf, shortcut, icon, callback});
	}

	void EditorWindow::AddMenuSeparator(const std::vector<Nz::LocalizedText>& path)
	{
		MenuList& parent = GetOrCreateMenuHierarchy(path);
		parent.entries.push_back(MenuSeparator{});
	}

	bool EditorWindow::HasMenuCategory(const std::string& category) const
	{
		return std::find_if(m_categories.begin(), m_categories.end(), [&category](auto&& cat) { return cat == category; })
			!= m_categories.end();
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
					if (arg.icon)
					{
						ImGui::Image(arg.icon.get(), Nz::Vector2{ 14, 14 });
						ImGui::SameLine();
					}
					if (ImGui::MenuItem(arg.label.c_str(), arg.shortcut.c_str()))
						arg.callback();
				},
				}, menu);
		};

		for (auto& menu : m_root.entries)
			visitor(menu);
	}

	EditorWindow::MenuList& EditorWindow::GetOrCreateMenuHierarchy(const std::vector<Nz::LocalizedText>& hierarchy)
	{
		auto getOrCreate_submenu = [](MenuList* menu, const Nz::LocalizedText& v) -> MenuList*
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
			
			menu->entries.push_back(MenuList{ v });
			return &std::get<MenuList>(menu->entries.back());
		};
		
		MenuList* currentMenu = &m_root;
		for (auto& entry : hierarchy)
			currentMenu = getOrCreate_submenu(currentMenu, entry);

		return *currentMenu;
	}
}