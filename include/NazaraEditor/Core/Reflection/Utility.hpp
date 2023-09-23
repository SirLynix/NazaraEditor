#pragma once

#include <NazaraEditor/Core/Reflection/Reflection.hpp>

#include <Nazara/Utility/Components/NodeComponent.hpp>

#include <imgui.h>

namespace Nz
{

	template <>
	class TypeReflect<NodeComponent>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, NodeComponent& obj)
		{
			p.AddProperty([&obj]() { return obj.GetPosition(); }, [&obj](const Nz::Vector3f& v) { return obj.SetPosition(v); }, "Position", "Position of the node");
			p.AddProperty([&obj]() { return obj.GetRotation(); }, [&obj](const Nz::Quaternionf& v) { return obj.SetRotation(v); }, "Rotation", "Rotation of the node");
			p.AddProperty([&obj]() { return obj.GetScale(); }, [&obj](const Nz::Vector3f& v) { return obj.SetScale(v); }, "Scale", "Scale of the node");
		}
	};

	namespace EditorImgui
	{
		inline bool Begin(Nz::NodeComponent& obj, const std::string& name, const std::string& tooltip)
		{
			return ImGui::TreeNode("NodeComponent");
		}

		inline void End(Nz::NodeComponent&) {
			ImGui::TreePop();
		}
	}
}