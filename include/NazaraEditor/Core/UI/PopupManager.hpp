#pragma once

#include <NazaraEditor/Core/Core.hpp>

#include <memory>
#include <vector>

namespace Nz
{
	struct EditorPopupParameters
	{
		struct Choice
		{
			std::string name;
			std::function<void(void)> callback;
		};
		std::string title;
		std::string description;
		std::vector<Choice> choices;
	};

	class EditorPopup
		: public Nz::ImguiHandler
	{
	public:
		EditorPopup(uint64_t id, const EditorPopupParameters& parameters);
		~EditorPopup();

		void OnRenderImgui() override;

		uint64_t GetId() const { return m_id; }

	private:
		uint64_t m_id;
		EditorPopupParameters m_parameters;
	};

	class NAZARAEDITOR_CORE_API EditorPopupManager
	{
	public:
		void Update();

		uint64_t CreatePopup(const EditorPopupParameters& parameters);
		void DestroyPopup(uint64_t popupId);

	private:
		EditorPopupManager();

		EditorPopupManager(const EditorPopupManager&) = delete;
		EditorPopupManager& operator=(const EditorPopupManager&) = delete;

		EditorPopupManager(EditorPopup&&) noexcept = delete;
		EditorPopupManager& operator=(EditorPopup&&) = delete;

		void DestroyPopupInternal(uint64_t popupId);

		uint64_t m_currentIndex;
		std::vector<std::unique_ptr<EditorPopup>> m_popups;
		std::vector<uint64_t> m_popupsToDelete;

		friend class EditorBaseApplication;
	};
}