#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/ModuleBase.hpp>
#include <Nazara/Graphics/Graphics.hpp>

#include <NazaraImgui/NazaraImgui.hpp>
#include <NazaraLocalization/Localization.hpp>

namespace Nz
{
    class NAZARAEDITOR_CORE_API EditorCore : public Nz::ModuleBase<EditorCore>
    {
        friend ModuleBase;

    public:
        using Dependencies = TypeList<Imgui, Localization, Graphics>;

        struct Config {};

        EditorCore(Config config);
        ~EditorCore();

    private:
        static EditorCore* s_instance;
    };
}