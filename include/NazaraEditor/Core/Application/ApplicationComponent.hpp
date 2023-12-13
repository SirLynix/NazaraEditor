#pragma once

#include <NazaraEditor/Core/Config.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

#include <Nazara/Core/ApplicationComponent.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorApplicationComponent
		: public EditorBaseApplication, public ApplicationComponent
	{
	public:
		EditorApplicationComponent(ApplicationBase& app);

		void Update(Time elapsedTime) override;
	};
}