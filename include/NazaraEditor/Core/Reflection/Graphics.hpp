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

	template <>
	class TypeReflect<CameraComponent>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, CameraComponent& obj)
		{
			p.AddProperty([&obj]() { return obj.GetZNear(); }, [&obj](float v) { obj.UpdateZNear(v); }, "Near", "Near plane");
			p.AddProperty([&obj]() { return obj.GetZFar(); }, [&obj](float v) { obj.UpdateZFar(v); }, "Far", "Far plane");
			p.AddProperty([&obj]() { return obj.GetFOV(); }, [&obj](Nz::DegreeAnglef v) { obj.UpdateFOV(v); }, "FOV", "Field of View");
			p.AddProperty([&obj]() { return obj.GetFOV(); }, [&obj](Nz::DegreeAnglef v) { obj.UpdateFOV(v); }, "FOV", "Field of View");
			p.AddProperty([&obj]() { return obj.GetClearColor(); }, [&obj](const Nz::Color& v) { obj.UpdateClearColor(v); }, "Clear color", "Clear color");
			p.AddProperty([&obj]() { return obj.GetRenderOrder(); }, [&obj](Nz::UInt32 v) { obj.UpdateRenderOrder(v); }, "RenderOrder", "Render order");
			p.AddProperty([&obj]() { return obj.GetRenderMask(); }, [&obj](Nz::UInt32 v) { obj.UpdateRenderMask(v); }, "RenderMask", "Render mask");
		}
	};


	namespace EditorImgui
	{
		inline bool Begin(Nz::LightComponent::LightEntry& /*obj*/, const std::string& /*name*/, const std::string& /*tooltip*/)
		{
			return false;
		}

		inline void End(Nz::LightComponent::LightEntry&) {
		}

		inline bool Begin(Nz::LightComponent& /*obj*/, const std::string& /*name*/, const std::string& /*tooltip*/)
		{
			return ImGui::TreeNodeEx("LightComponent", ImGuiTreeNodeFlags_Framed);
		}

		inline void End(Nz::LightComponent&) {
			ImGui::TreePop();
		}

		inline bool Begin(Nz::CameraComponent& /*obj*/, const std::string& /*name*/, const std::string& /*tooltip*/)
		{
			return ImGui::TreeNodeEx("CameraComponent", ImGuiTreeNodeFlags_Framed);
		}

		inline void End(Nz::CameraComponent&) {
			ImGui::TreePop();
		}
	}
}