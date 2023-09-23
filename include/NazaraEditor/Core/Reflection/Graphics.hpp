#pragma once

#include <NazaraEditor/Core/Reflection/Reflection.hpp>

#include <Nazara/Graphics.hpp>

#include <imgui.h>

namespace Nz
{
	template <>
	class TypeReflect<LightComponent::LightEntry>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, LightComponent::LightEntry& obj)
		{
		}
	};

	template <>
	class TypeReflect<LightComponent>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, LightComponent& obj)
		{
			p.AddProperty([&obj]() { return obj.IsVisible(); }, [&obj](bool v) { obj.Show(v); }, "Is Visible", "Toggles lights visibility");
			//p.AddProperty(obj.GetLights(), "Lights", "");
		}
	};

	namespace EditorImgui
	{
		inline bool Begin(Nz::LightComponent::LightEntry& obj, const std::string& name, const std::string& tooltip)
		{
			return false;
		}

		inline void End(Nz::LightComponent::LightEntry&) {
		}

		inline bool Begin(Nz::LightComponent& obj, const std::string& name, const std::string& tooltip)
		{
			return ImGui::TreeNode("LightComponent");
		}

		inline void End(Nz::LightComponent&) {
			ImGui::TreePop();
		}
	}
}