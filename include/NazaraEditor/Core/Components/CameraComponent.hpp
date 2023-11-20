#pragma once

#include <NazaraEditor/Core/Core.hpp>

#include <Nazara/Platform/WindowEventHandler.hpp>

namespace Nz
{
	class NodeComponent;
	class WindowEventHandler;

	class NAZARAEDITOR_CORE_API EditorCameraComponent
	{
	public:
		EditorCameraComponent();
		EditorCameraComponent(const EditorCameraComponent&) = delete;

		EditorCameraComponent(EditorCameraComponent&&);
		~EditorCameraComponent();

		void Update(Time elapsedTime, NodeComponent& node);

		inline void SetPosition(const Nz::Vector3f& position) { m_targetPosition = position; }
		inline void SetRotation(const Nz::Quaternionf& rotation) { m_targetAngles = rotation.ToEulerAngles(); }

		inline const Nz::Vector3f& GetPosition() const { return m_targetPosition; }
		inline const Nz::EulerAnglesf& GetOrientation() const { return m_targetAngles; }

	private:
		NazaraSlot(Nz::WindowEventHandler, OnMouseMoved, m_onMouseMoved);

		Nz::EulerAnglesf m_targetAngles;
		Nz::Vector3f m_targetPosition;
		Nz::Vector3f m_currentVelocity;

		float m_moveSpeed;
		float m_smoothSpeed;
	};
}