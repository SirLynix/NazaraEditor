#pragma once

#include <NazaraEditor/Core/Reflection/Reflection.hpp>
#include <NazaraEditor/Core/Reflection/Math.hpp>

#include <Nazara/Core.hpp>
#include <Nazara/Utility.hpp>

#include <array>
#include <vector>
#include <string>
#include <imgui.h>

namespace Nz
{
	template <>
	class TypeReflect<Color>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, Color& obj)
		{
			p.AddProperty(obj.r, "R", "Red (0-255)");
			p.AddProperty(obj.g, "G", "Green (0-255)");
			p.AddProperty(obj.b, "B", "Blue (0-255)");
			p.AddProperty(obj.a, "A", "Alpha (0-255)");
		}
	};

	namespace EditorImgui
	{
		inline bool Begin(Color& obj, const std::string& name, const std::string& tooltip)
		{
			// your IMGUI Code
			float values[] = { obj.r, obj.g, obj.b, obj.a };
			if (ImGui::ColorEdit4(name.c_str(), values, ImGuiColorEditFlags_PickerHueWheel))
			{
				obj = Color(values[0], values[1], values[2], values[3]);
			}
			return false;
		}

		inline void End(Color&) {}
	}

	// Wrapper for array values
	template <typename T>
	struct ArrayEntry
	{
		T& value;
	};

	template <typename T>
	class TypeReflect<ArrayEntry<T>>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, ArrayEntry<T>& obj)
		{
			p.AddProperty(p.value, "", "");
		}
	};

	template <typename T, size_t Size>
	class TypeReflect<std::array<T, Size>>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, std::array<T, Size>& obj)
		{
			for (size_t i = 0; i < Size; ++i)
			{
				p.AddProperty(ArrayEntry{ obj[i] }, "", "");
			}
		}
	};

	namespace EditorImgui
	{
		template <typename T, size_t Size>
		static bool Begin(ArrayEntry<T>& obj, const std::string& name, const std::string& tooltip)
		{
			ImGui::BeginGroup();
		}

		template <typename T, size_t Size>
		static void End(ArrayEntry<T>&) {
			ImGui::EndGroup();
		}

		template <typename T, size_t Size>
		static bool Begin(std::array<T, Size>& obj, const std::string& name, const std::string& tooltip)
		{
			return ImGui::TreeNode(name.c_str());
		}

		template <typename T, size_t Size>
		static void End(std::array<T, Size>&) {
			ImGui::TreePop();
		}
	}



	template <>
	class TypeReflect<entt::handle>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, entt::handle& obj)
		{
			for (auto&& curr : obj.storage())
			{
				if (auto& storage = curr.second; storage.contains(obj))
				{
					entt::id_type id = curr.first;
					if (auto reflect = entt::resolve(id).func(entt::hashed_string("Reflect")); reflect)
						reflect.invoke({}, p, obj);
				}
			}
		}
	};

	namespace EditorImgui
	{
		static bool Begin(entt::handle& obj, const std::string& name, const std::string& tooltip)
		{
			std::string n = "Entity " + name;
			return ImGui::TreeNode(n.c_str());
		}

		static void End(entt::handle&) {
			ImGui::TreePop();
		}
	}

	template <typename TPropertyEnumerator, typename TComponent>
	inline void ReflectComponent(TPropertyEnumerator& p, entt::handle& obj)
	{
		TComponent* component = obj.try_get<TComponent>();
		if (component != nullptr)
			p.AddProperty(*component, "", "");
	}
}