#pragma once

#include <imgui.h>

namespace Nz
{
	template <typename T>
	class TypeReflect
	{
	public:
		template <typename TEnumerator>
		static void Reflect(TEnumerator&, T&) {	} // default specialization
	};

	namespace EditorImgui
	{
		inline void Tooltip(const std::string& tooltip)
		{
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text(tooltip.c_str());
				ImGui::EndTooltip();
			}
		}
	}
}