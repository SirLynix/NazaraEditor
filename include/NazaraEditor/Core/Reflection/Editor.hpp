#pragma once

#include <functional>
#include <string>

namespace Nz
{
	template <>
	class TypeReflect<EditorNameComponent>
	{
	public:
		template <typename TPropertyEnumerator>
		static void Reflect(TPropertyEnumerator& p, EditorNameComponent& obj)
		{
			p.AddProperty([&obj]() { return obj.GetName(); }, [&obj](const std::string& v) { obj.SetName(v); }, "Name", "Entity Name");
		}
	};

	namespace EditorImgui
	{
		inline bool Begin(Nz::EditorNameComponent& /*obj*/, const std::string& /*name*/, const std::string& /*tooltip*/) { return true; }

		inline void End(Nz::EditorNameComponent& /*obj*/) {	}
	}

	template <typename TPropertyDetail>
	struct EditorPropertyInspector
	{
		template <typename T>
		void AddProperty(T& prop, const std::string& name, const std::string& tooltip);

		template <typename T>
		void AddPropertyNoWrapper(T& prop, const std::string& name, const std::string& tooltip);

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