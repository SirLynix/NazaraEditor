#include <NazaraEditor/Core/UI/PopupManager.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	
	EditorPopup::EditorPopup(uint64_t id, const EditorPopupParameters& parameters)
		: m_id(id)
		, m_parameters(parameters)
	{
		Nz::Imgui::Instance()->AddHandler(this);
	}

	EditorPopup::~EditorPopup()
	{
		Nz::Imgui::Instance()->RemoveHandler(this);
	}

	void EditorPopup::OnRenderImgui()
	{
		ImGui::OpenPopup(m_parameters.title.c_str());
		if (ImGui::BeginPopupModal(m_parameters.title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::Text(m_parameters.description.c_str());

			for (auto&& choice : m_parameters.choices)
			{
				if (ImGui::Button(choice.name.c_str()))
				{
					if (choice.callback)
						choice.callback();

					EditorBaseApplication::Instance()->GetPopupManager().DestroyPopup(m_id);
				}
				ImGui::SameLine();
			}

			ImGui::EndPopup();
		}
	}

	EditorPopupManager::EditorPopupManager()
		: m_currentIndex(0)
	{}

	void EditorPopupManager::Update()
	{
		for (uint64_t id : m_popupsToDelete)
			DestroyPopupInternal(id);
		m_popupsToDelete.clear();
	}

	uint64_t EditorPopupManager::CreatePopup(const EditorPopupParameters& parameters)
	{
		int64_t currentIndex = m_currentIndex++;
		m_popups.push_back(std::make_unique<EditorPopup>(currentIndex, parameters));
		return currentIndex;
	}

	void EditorPopupManager::DestroyPopup(uint64_t popupId)
	{
		m_popupsToDelete.push_back(popupId);
	}

	void EditorPopupManager::DestroyPopupInternal(uint64_t popupId)
	{
		auto it = std::find_if(m_popups.begin(), m_popups.end(), [popupId](auto&& popup) { return popup->GetId() == popupId; });
		if (it == m_popups.end())
			return;

		m_popups.erase(it);
	}

}