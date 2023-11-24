#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/Clock.hpp>
#include <Nazara/Platform/WindowEventHandler.hpp>
#include <Nazara/Math/Ray.hpp>

namespace Nz
{
	class Camera;
	class DebugDrawer;
	class NodeComponent;
	class WindowEventHandler;

	class NAZARAEDITOR_CORE_API EditorCameraComponent
	{
	public:
		EditorCameraComponent(Nz::Camera& camera, Nz::DebugDrawer& debug);
		EditorCameraComponent(const EditorCameraComponent&) = delete;

		EditorCameraComponent(EditorCameraComponent&&);
		~EditorCameraComponent();

		void Update(Time elapsedTime, NodeComponent& node);

		inline void SetPosition(const Nz::Vector3f& position) { m_targetPosition = position; }
		inline void SetRotation(const Nz::Quaternionf& rotation) { m_targetAngles = rotation.ToEulerAngles(); }

		inline const Nz::Vector3f& GetPosition() const { return m_targetPosition; }
		inline const Nz::EulerAnglesf& GetOrientation() const { return m_targetAngles; }

	private:
		void RaycastSelection(int x, int y);

		NazaraSlot(Nz::WindowEventHandler, OnMouseButtonReleased, m_onMouseClicked);
		NazaraSlot(Nz::WindowEventHandler, OnMouseMoved, m_onMouseMoved);

		Nz::Camera& m_camera;
		Nz::EulerAnglesf m_targetAngles;
		Nz::Vector3f m_targetPosition;
		Nz::Vector3f m_currentVelocity;

		float m_moveSpeed;
		float m_smoothSpeed;
	
		Nz::Rayf m_lastRay;
		Nz::DebugDrawer& m_debugDrawer;
		Nz::MillisecondClock m_debugClock;
	};
}