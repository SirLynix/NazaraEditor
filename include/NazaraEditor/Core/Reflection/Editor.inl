
namespace Nz
{

	template <typename TPropertyDetail>
	template <typename T> void EditorPropertyInspector<TPropertyDetail>::AddProperty(T& prop, const std::string& name, const std::string& tooltip)
	{
		if (TPropertyDetail::Begin(prop, name, tooltip))
		{
			TypeReflect<T>::Reflect(*this, prop);
			TPropertyDetail::End(prop);
		}
	}

	template <typename TPropertyDetail>
	template <typename T> void EditorPropertyInspector<TPropertyDetail>::AddPropertyNoWrapper(T& prop, const std::string& name, const std::string& tooltip)
	{
		TypeReflect<T>::Reflect(*this, prop);
	}

}