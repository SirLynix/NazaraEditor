#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/ModuleBase.hpp>
#include <NazaraImgui/NazaraImgui.hpp>

namespace Nz
{
    class NAZARAEDITOR_CORE_API EditorCore : public Nz::ModuleBase<EditorCore>
    {
        friend ModuleBase;

    public:
        using Dependencies = TypeList<Imgui>;

        struct Config {};

        EditorCore(Config config);
        ~EditorCore();

    private:
        static EditorCore* s_instance;
    };
}