#pragma once

#include <NazaraEditor/Core/Reflection/Reflection.hpp>
#include <Nazara/Math.hpp>

#include <imgui.h>

namespace Nz
{
	namespace EditorImgui
	{
		inline bool Begin(bool& obj, const std::string& name, const std::string& tooltip)
		{
			ImGui::Checkbox(name.c_str(), &obj);
			Tooltip(tooltip);
			return false;
		}

		inline void End(bool&) {}

#define IMGUI_BASIC_INTEGER(Type) \
		inline bool Begin(Type& obj, const std::string& name, const std::string& tooltip) \
		{ \
			int value = static_cast<int>(obj); \
			if (ImGui::DragInt(name.c_str(), &value, 1.f, std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max())) \
				obj = static_cast<Type>(value); \
			Tooltip(tooltip); \
			return false; \
		} \
		inline void End(Type&) {}

		IMGUI_BASIC_INTEGER(Nz::Int8);
		IMGUI_BASIC_INTEGER(Nz::Int16)
		IMGUI_BASIC_INTEGER(Nz::Int32);
		IMGUI_BASIC_INTEGER(Nz::Int64);
		IMGUI_BASIC_INTEGER(Nz::UInt8);
		IMGUI_BASIC_INTEGER(Nz::UInt16);
		IMGUI_BASIC_INTEGER(Nz::UInt32);
		IMGUI_BASIC_INTEGER(Nz::UInt64);

#define IMGUI_BASIC_FLOAT(Type) \
		inline bool Begin(Type& obj, const std::string& name, const std::string& tooltip) \
		{ \
			float value = (float)obj; \
			if (ImGui::DragFloat(name.c_str(), &value, 1.f, std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max())) \
				obj = (Type)value; \
			Tooltip(tooltip); \
			return false; \
		} \
		inline void End(Type&) {}

		IMGUI_BASIC_FLOAT(float);
		IMGUI_BASIC_FLOAT(double);


		inline bool Begin(Nz::Vector3f& obj, const std::string& name, const std::string& tooltip)
		{
			float value[] = { obj.x, obj.y, obj.z };
			if (ImGui::DragFloat3(name.c_str(), value, 1.f, std::numeric_limits<float>::min(), std::numeric_limits<float>::max()))
				obj = Nz::Vector3f(value[0], value[1], value[2]);
			Tooltip(tooltip);
			return false;
		}
			
		inline void End(Nz::Vector3f&) {}


		inline bool Begin(Nz::Quaternionf& obj, const std::string& name, const std::string& tooltip)
		{
			auto euler = obj.ToEulerAngles();
			float value[] = { euler.pitch.ToDegrees(), euler.yaw.ToDegrees(), euler.roll.ToDegrees() };
			if (ImGui::DragFloat3(name.c_str(), value, 1.f, std::numeric_limits<float>::min(), std::numeric_limits<float>::max()))
			{
				obj = EulerAnglesf(value[0], value[1], value[2]).ToQuaternion();
			}
			Tooltip(tooltip);
			return false;
		}

		inline void End(Nz::Quaternionf&) {}

		template <AngleUnit Unit, typename T>
		inline bool Begin(Nz::Angle<Unit, T>& obj, const std::string& name, const std::string& tooltip)
		{
			auto angle = obj.To<Unit>();
			if (ImGui::DragFloat(name.c_str(), &angle, 1.f, std::numeric_limits<float>::min(), std::numeric_limits<float>::max()))
			{
				obj.From<Unit>(angle);
			}
			Tooltip(tooltip);
			return false;
		}

		template <AngleUnit Unit, typename T>
		inline void End(Nz::Angle<Unit, T>& /*obj*/) {}
	}

}