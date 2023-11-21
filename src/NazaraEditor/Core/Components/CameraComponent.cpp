#include <NazaraEditor/Core/Components/CameraComponent.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

#include <Nazara/Graphics/Components/CameraComponent.hpp>
#include <Nazara/Math/Ray.hpp>

namespace
{
	// Unity SmoothDamp function
	template <typename T>
	T SmoothDamp(T current, T target, T& currentVelocity, float smoothTime, Nz::Time deltaTime)
	{
		if (current.SquaredDistance(target) < 0.0001f)
			return target;

		// Based on Game Programming Gems 4 Chapter 1.10
		smoothTime = std::max(0.0001f, smoothTime);
		float omega = 2.f / smoothTime;

		float x = omega * deltaTime.AsSeconds();
		float exp = 1.f / (1.f + x + 0.48f * x * x + 0.235f * x * x * x);
		T change = current - target;
		T originalTo = target;

		// Clamp maximum speed
		float maxChange = smoothTime;
		float dist = change.GetLength();
		dist = Nz::Clamp(dist, -maxChange, maxChange);
		target = current - change.Normalize() * dist;

		T temp = (currentVelocity + omega * change) * deltaTime.AsSeconds();
		currentVelocity = (currentVelocity - omega * temp) * exp;
		T output = target + (change + temp) * exp;

		// Prevent overshooting
		if (current.SquaredDistance(target) <= current.SquaredDistance(output))
		{
			output = originalTo;
			currentVelocity = (output - originalTo) / deltaTime.AsSeconds();
		}

		return output;
	}
}

namespace Nz
{
	EditorCameraComponent::EditorCameraComponent(Nz::Camera& camera, Nz::DebugDrawer& debugDrawer)
		: m_camera(camera)
		, m_debugDrawer(debugDrawer)
		, m_targetAngles(Nz::EulerAnglesf::Zero())
		, m_targetPosition(Nz::Vector3f::Zero())
		, m_currentVelocity(Nz::Vector3f::Zero())
		, m_moveSpeed(3.f)
		, m_smoothSpeed(0.3f)
	{
		auto& handler = EditorBaseApplication::Instance()->GetWindow()->GetEventHandler();

		m_onMouseClicked.Connect(handler.OnMouseButtonReleased, [&](const Nz::WindowEventHandler*, const Nz::WindowEvent::MouseButtonEvent& event)
		{
			if (event.button == Nz::Mouse::Button::Left)
			{
				RaycastSelection(event.x, event.y);
			}
		});

		m_onMouseMoved.Connect(handler.OnMouseMoved, [&](const Nz::WindowEventHandler*, const Nz::WindowEvent::MouseMoveEvent& event)
			{
				if (Nz::Mouse::IsButtonPressed(Nz::Mouse::Button::Right))
				{
					// Gestion de la caméra free-fly (Rotation)
					float sensitivity = 0.1f; // Sensibilité de la souris

					auto delta = Nz::Vector2i{ event.deltaX, event.deltaY };

					// On modifie l'angle de la caméra grâce au déplacement relatif sur X de la souris
					m_targetAngles.yaw = m_targetAngles.yaw - delta.x * sensitivity;
					m_targetAngles.yaw.Normalize();

					// Idem, mais pour éviter les problèmes de calcul de la matrice de vue, on restreint les angles
					m_targetAngles.pitch = Nz::Clamp(m_targetAngles.pitch - delta.y * sensitivity, -89.f, 89.f);
				}
			});
	}

	EditorCameraComponent::~EditorCameraComponent()
	{
		m_onMouseMoved.Disconnect();
	}

	void EditorCameraComponent::Update(Time elapsedTime, NodeComponent& node)
	{
		auto currentRotation = m_targetAngles.ToQuaternion();
		auto currentPosition = m_targetPosition;
		// todo use action mapping
		if (Nz::Mouse::IsButtonPressed(Nz::Mouse::Button::Right))
		{
			Nz::Vector3f delta = Nz::Vector3f::Zero();
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::W))
				delta += Nz::Vector3f::Forward();
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::S))
				delta += Nz::Vector3f::Backward();
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::A))
				delta += Nz::Vector3f::Left();
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::D))
				delta += Nz::Vector3f::Right();
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Q))
				delta += Nz::Vector3f::Up();
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::E))
				delta += Nz::Vector3f::Down();

			m_targetPosition += (currentRotation * delta) * elapsedTime.AsSeconds() * m_moveSpeed;
			currentPosition = SmoothDamp(node.GetPosition(), m_targetPosition, m_currentVelocity, m_smoothSpeed, elapsedTime);
		}

		node.SetPosition(currentPosition);
		node.SetRotation(currentRotation);

		if (!m_debugClock.IsPaused())
		{
			if (m_debugClock.GetElapsedTime().AsSeconds() > 100)
				m_debugClock.Pause();

			m_debugDrawer.DrawLine(m_lastRay.origin, m_lastRay.direction * 500 + m_lastRay.origin, Nz::Color::Green());
		}
	}

	void EditorCameraComponent::RaycastSelection(int x, int y)
	{
		auto near = m_camera.Unproject(Nz::Vector3f(x, y, 0));
		auto far = m_camera.Unproject(Nz::Vector3f(x, y, 1));

		Nz::Rayf ray(near, (far - near).Normalize());

		auto entities = EditorBaseApplication::Instance()->GetLevel().Raycast(ray);

		if (!entities.empty())
		{
			EditorBaseApplication::Instance()->OnEntitySelected(entities.front().entity);
		}

		m_lastRay = ray;
		m_debugClock.Restart();
	}
}