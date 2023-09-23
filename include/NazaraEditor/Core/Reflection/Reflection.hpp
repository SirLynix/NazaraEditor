#pragma once

namespace Nz
{
	template <typename T>
	class TypeReflect
	{
	public:
		template <typename TEnumerator>
		static void Reflect(TEnumerator&, T&) {	} // default specialization
	};
}