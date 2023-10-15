#pragma once

#include <NazaraEditor/Core/Core.hpp>
#include <Nazara/Platform.hpp>

#include <vector>

namespace Nz
{
	struct NAZARAEDITOR_CORE_API Shortcut
	{
		bool bCtrl : 1;
		bool bShift : 1;
		std::vector<Nz::Keyboard::VKey> keys;

		std::string ToString() const
		{
			std::ostringstream oss;
			if (bCtrl) oss << "Ctrl+";
			if (bShift) oss << "Shift+";
			for (size_t i = 0; i < keys.size(); ++i)
			{
				oss << Nz::Keyboard::GetKeyName(keys[i]);
				if (i < keys.size() - 1)
					oss << "+";
			}
			return oss.str();
		}

		static Shortcut Create(Nz::Keyboard::VKey key, bool bCtrl, bool bShift)
		{
			Shortcut shortcut
			{
				.bCtrl = bCtrl,
				.bShift = bShift,
				.keys = { key }
			};
			return shortcut;
		}
	};
}