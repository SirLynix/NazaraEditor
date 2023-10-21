#pragma once

#include <NazaraEditor/Core/Config.hpp>
#include <NazaraEditor/Core/Application/Action.hpp>

#include <memory>
#include <vector>

namespace Nz
{
	class NAZARAEDITOR_CORE_API ActionStack final
	{
	public:
		void ExecuteAction(const std::string& name)
		{
			ExecuteAction(CreateAction(name));
		}

		void ExecuteAction(const std::shared_ptr<EditorAction>& action)
		{
			if (!action)
				return;

			if (!action->IsUndoRedoable())
			{
				action->Execute();
				return;
			}

			if (CanRedo())
			{
				// erase stack content after current index
				m_undoRedoStack.resize(m_currentIndex);
			}

			m_undoRedoStack.push_back(std::move(action));
			Redo();
		}
		
		std::shared_ptr<EditorAction> CreateAction(const std::string& name)
		{
			auto it = std::find_if(m_availableActions.begin(), m_availableActions.end(), [&name](auto&& action) { return action->GetName() == name; });
			if (it == m_availableActions.end())
				return {};

			return std::shared_ptr<EditorAction>((*it)->Clone());
		}

		void Undo();
		bool CanUndo() const;

		void Redo();
		bool CanRedo() const;


	protected:
		ActionStack();

		ActionStack(ActionStack&) = delete;
		ActionStack& operator=(const ActionStack&) = delete;
		ActionStack(ActionStack&&) = delete;
		ActionStack& operator=(ActionStack&&) = delete;

		template <typename TAction, typename... TArgs>
		void RegisterAction(const EditorAction::Properties& properties, TArgs&&... args)
		{
			m_availableActions.push_back(std::make_unique<TAction>(properties, std::forward<TArgs...>(args)...));
		}

		int64_t m_currentIndex;
		std::vector<std::shared_ptr<EditorAction>> m_undoRedoStack;

		std::vector<std::unique_ptr<EditorAction>> m_availableActions;

		friend class EditorBaseApplication;
	};
}