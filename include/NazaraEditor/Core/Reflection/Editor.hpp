#pragma once

#include <functional>
#include <string>

namespace Nz
{
	template <typename TPropertyDetail>
	struct EditorPropertyInspector
	{
		template <typename T>
		void AddProperty(T& prop, const std::string& name, const std::string& tooltip);

		/*template <typename T, typename U, typename V>
		void AddProperty(T& parent, V(U::* Getter)() const, void(U::*Setter(const V&))(), const std::string& name, const std::string& tooltip)
		{
			U val = parent->Getter();
			AddProperty(val, name, tooltip);
			parent->Setter(val);
		}*/

		template <typename TGetter, typename TSetter>
		void AddProperty(TGetter Getter, TSetter Setter, const std::string& name, const std::string& tooltip)
		{
			auto val = Getter();
			AddProperty(val, name, tooltip);
			Setter(val);
		}
	};

	struct EditorRenderer
	{
		template <typename T>
		static bool Begin(T& prop, const std::string& name, const std::string& tooltip)
		{
			return EditorImgui::Begin(prop, name, tooltip);
		}

		template <typename T>
		static void End(T& prop)
		{
			EditorImgui::End(prop);
		}
	};
}

#include <NazaraEditor/Core/Reflection/Editor.inl>