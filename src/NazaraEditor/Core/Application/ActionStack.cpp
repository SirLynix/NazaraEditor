#include <NazaraEditor/Core/Application/ActionStack.hpp>

namespace Nz
{
	ActionStack* ActionStack::s_instance = nullptr;
	ActionStack::ActionStack()
		: m_currentIndex(0)
	{
		NazaraAssert(s_instance == nullptr, "ActionStack already exists");
		s_instance = this;
	}

	ActionStack::~ActionStack()
	{
		s_instance = nullptr;
	}

	ActionStack* ActionStack::Instance()
	{
		return s_instance;
	}


	bool ActionStack::CanUndo() const { return !m_undoRedoStack.empty() && m_currentIndex >= 0; }
	void ActionStack::Undo()
	{
		if (!CanUndo())
			return;

		m_undoRedoStack[m_currentIndex--]->Revert();
	}

	bool ActionStack::CanRedo() const { return !m_undoRedoStack.empty() && m_currentIndex < m_undoRedoStack.size(); }
	void ActionStack::Redo()
	{
		if (!CanRedo())
			return;

		m_undoRedoStack[m_currentIndex++]->Execute();
	}
}