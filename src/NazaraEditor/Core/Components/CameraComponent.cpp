#include <NazaraEditor/Core/Components/CameraComponent.hpp>

#include <NazaraEditor/Core/Application/BaseApplication.hpp>

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
	EditorCameraComponent::EditorCameraComponent()
		: m_moveSpeed(3.f)
		, m_smoothSpeed(0.3f)
	{
		auto& handler = EditorBaseApplication::Instance()->GetWindow()->GetEventHandler();

		m_onMouseMoved.Connect(handler.OnMouseMoved, [&](const Nz::WindowEventHandler*, const Nz::WindowEvent::MouseMoveEvent& event)
			{
				// Gestion de la caméra free-fly (Rotation)
				float sensitivity = 0.3f; // Sensibilité de la souris

				// On modifie l'angle de la caméra grâce au déplacement relatif sur X de la souris
				m_targetAngles.yaw = m_targetAngles.yaw - event.deltaX * sensitivity;
				m_targetAngles.yaw.Normalize();

				// Idem, mais pour éviter les problèmes de calcul de la matrice de vue, on restreint les angles
				m_targetAngles.pitch = Nz::Clamp(m_targetAngles.pitch - event.deltaY * sensitivity, -89.f, 89.f);
			});
	}

	EditorCameraComponent::~EditorCameraComponent()
	{
		m_onMouseMoved.Disconnect();
	}

	void EditorCameraComponent::Update(Time elapsedTime, NodeComponent& node)
	{
		// todo use action mapping
		Nz::Vector3f delta;
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

		auto currentRotation = m_targetAngles.ToQuaternion();
		m_targetPosition += (currentRotation * delta) * elapsedTime.AsSeconds() * m_moveSpeed;

		auto currentPosition = SmoothDamp(node.GetPosition(), m_targetPosition, m_currentVelocity, m_smoothSpeed, elapsedTime);
		node.SetPosition(currentPosition);
		node.SetRotation(currentRotation);
	}
}