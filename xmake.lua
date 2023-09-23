set_project("NazaraEditor")

add_rules("mode.asan", "mode.tsan", "mode.coverage", "mode.debug", "mode.releasedbg", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

includes("xmake/**.lua")

add_repositories("nazara-engine-repo https://github.com/NazaraEngine/xmake-repo")
add_repositories("nazara-imgui-repo https://github.com/SweetId/NazaraImgui-xmake-repo")
add_requires("nazaraengine", { alias = "nazara", debug = is_mode("debug") })
add_requires("nazaraimgui", { alias = "nzimgui", debug = is_mode("debug") })

add_includedirs("include", "src")
set_languages("c89", "c++17")
set_rundir("./bin/$(plat)_$(arch)_$(mode)")
set_targetdir("./bin/$(plat)_$(arch)_$(mode)")

if has_config("erronwarn") then
	set_warnings("allextra", "error")
else
	set_warnings("allextra")
end

if is_plat("mingw", "linux") then
	add_cxflags("-Wno-subobject-linkage")
end

if is_plat("windows") then
	add_defines("_CRT_SECURE_NO_WARNINGS")
	add_cxxflags("/bigobj", "/permissive-", "/Zc:__cplusplus", "/Zc:externConstexpr", "/Zc:inline", "/Zc:lambda", "/Zc:preprocessor", "/Zc:referenceBinding", "/Zc:strictStrings", "/Zc:throwingNew")
	add_cxflags("/w44062") -- Enable warning: switch case not handled
	add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
	add_cxflags("/wd4275") -- Disable warning: DLL-interface class 'class_1' used as base for DLL-interface blah
elseif is_plat("mingw") then
	add_cxflags("-Og", "-Wa,-mbig-obj")
	add_ldflags("-Wa,-mbig-obj")
end

if is_mode("debug") then
	set_runtimes("MDd")
elseif is_mode("asan", "tsan", "ubsan") then
	set_optimize("none") -- by default xmake will optimize asan builds
elseif is_mode("coverage") then
	if not is_plat("windows") then
		add_links("gcov")
	end
elseif is_mode("releasedbg") then
	set_runtimes("MD")
	set_fpmodels("fast")
	add_vectorexts("sse", "sse2", "sse3", "ssse3")
end

local modules = {
	Core = {
		Packages = { "nazara", "nzimgui" },
	}
}

function ModuleTargetConfig(name, module)
	add_defines("NAZARAEDITOR_" .. name:upper() .. "_BUILD")
	if is_mode("debug") then
		add_defines("NAZARAEDITOR_" .. name:upper() .. "_DEBUG")
	end

	-- Add header and source files
	local headerExts = {".h", ".hpp", ".inl", ".natvis"}
	for _, ext in ipairs(headerExts) do
		add_headerfiles("include/(NazaraEditor/" .. name .. "/**" .. ext .. ")")
		add_headerfiles("src/NazaraEditor/" .. name .. "/**" .. ext, { prefixdir = "private", install = false })
		add_headerfiles("src/NazaraEditor/" .. name .. "/Resources/**.nzsl", { prefixdir = "private", install = false })
	end

	remove_headerfiles("src/NazaraEditor/" .. name .. "/Resources/**.h")

	add_files("src/NazaraEditor/" .. name .. "/**.cpp")
	if has_config("embed_resources") then
		local embedResourceRule = false
		for _, filepath in pairs(os.files("src/NazaraEditor/" .. name .. "/Resources/**|**.h|**.nzsl|**.nzslb")) do
			if not embedResourceRule then
				add_rules("embed.resources")
				embedResourceRule = true
			end

			add_files(filepath, {rule = "embed.resources"})
		end
	end

	if has_config("compile_shaders") then
		local compileShaderRule = false
		for _, filepath in pairs(os.files("src/NazaraEditor/" .. name .. "/Resources/**.nzsl")) do
			if not compileShaderRule then
				add_rules("nzsl.compile.shaders")
				compileShaderRule = true
			end

			add_files(filepath, {rule = "nzsl.compile.shaders"})
		end
	end

	-- Remove platform-specific files
	if not is_plat("windows", "mingw") then
		remove_headerfiles("src/NazaraEditor/" .. name .. "/Win32/**")
		remove_files("src/NazaraEditor/" .. name .. "/Win32/**")
	end

	if not is_plat("linux", "android", "cross") then
		remove_headerfiles("src/NazaraEditor/" .. name .. "/Linux/**")
		remove_files("src/NazaraEditor/" .. name .. "/Linux/**")
	end

	if not is_plat("macosx", "iphoneos") then
		remove_headerfiles("src/NazaraEditor/" .. name .. "/Darwin/**")
		remove_files("src/NazaraEditor/" .. name .. "/Darwin/**")
	end

	if not is_plat("linux", "macosx", "iphoneos", "android", "wasm", "cross") then
		remove_headerfiles("src/NazaraEditor/" .. name .. "/Posix/**")
		remove_files("src/NazaraEditor/" .. name .. "/Posix/**")
	end

	if module.Custom then
		module.Custom()
	end
end

for name, module in pairs(modules) do
	if module.Option and not has_config(module.Option) then
		goto continue
	end

	target("NazaraEditor-" .. name, function ()
		set_group("Modules")

		-- for now only shared compilation is supported (except on platforms like wasm)
		if not is_plat("wasm") then
			set_kind("shared")
		else
			set_kind("static")
			add_defines("NAZARAEDITOR_STATIC", { public = true })
		end

		add_rpathdirs("$ORIGIN")

		if module.Deps then
			add_deps(table.unpack(module.Deps))
		end

		if module.Packages then
			add_packages(table.unpack(module.Packages))
		end

		if module.PublicPackages then
			for _, pkg in ipairs(module.PublicPackages) do
				add_packages(pkg, { public = true })
			end
		end

		if has_config("usepch") then
			set_pcxxheader("include/NazaraEditor/" .. name .. ".hpp")
		end

		if has_config("unitybuild") then
			add_rules("c++.unity_build", {uniqueid = "NAZARA_UNITY_ID", batchsize = 12})
		end

		if is_plat("windows", "mingw") then
			add_defines("NAZARA_UTILS_WINDOWS_NT6=1")
		end

		add_includedirs("src")

		ModuleTargetConfig(name, module)
	end)

	::continue::
end

target("NazaraEditor")
	set_group("Applications")
	add_headerfiles("include/NazaraEditor/Editor/**.h")
	add_headerfiles("include/NazaraEditor/Editor/**.hpp")
	add_headerfiles("include/NazaraEditor/Editor/**.inl")
	add_files("src/NazaraEditor/Editor/**.cpp")

	for name, module in pairs(modules) do
		add_deps("NazaraEditor-" .. name)
	end
	add_packages("nazara", "nzimgui")
	set_rundir(".")