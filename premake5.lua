SRC_DIR = "src"
WORKSPACE_DIR = "workspace"
PROJECT_DIR = "%{wks.location}/%{prj.name}"
OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
BUILD_DIR = "premake-build"

workspace("cbtEngine")
    location(WORKSPACE_DIR)
    architecture("x86_64")
    configurations({"Debug", "Release"})
    startproject("cbtGame")

    filter("configurations:Debug")
        defines("CBT_DEBUG")
        symbols "On"
    filter({})

    filter("configurations:Release")
        defines("CBT_RELEASE")
        optimize "On"
    filter({})

    filter("system:windows")
        systemversion("latest")
        defines({"CBT_PLATFORM_WINDOWS"})
    filter({})

    filter("system:linux")
        systemversion("latest")
        defines({"CBT_PLATFORM_LINUX"})
    filter({})

project("cbtCore")
    location(PROJECT_DIR)
    language("C++")
    kind("StaticLib")

    targetdir(BUILD_DIR .. "/bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir(BUILD_DIR .. "/bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files({
        SRC_DIR .. "/%{prj.name}/**.h",
        SRC_DIR .. "/%{prj.name}/**.c",
        SRC_DIR .. "/%{prj.name}/**.hpp",
        SRC_DIR .. "/%{prj.name}/**.cpp",
    })

    links({
        "GL",
        "GLEW",
        "SDL2",
        "SDL2_image",
    })

    includedirs({
        SRC_DIR .. "/%{prj.name}",
    })

project("cbtGame")
    location(PROJECT_DIR)
    language("C++")
    kind("ConsoleApp")

    targetdir(BUILD_DIR .. "/bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir(BUILD_DIR .. "/bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files({
        SRC_DIR .. "/%{prj.name}/**.h",
        SRC_DIR .. "/%{prj.name}/**.c",
        SRC_DIR .. "/%{prj.name}/**.hpp",
        SRC_DIR .. "/%{prj.name}/**.cpp",
    })

    links({
        "GL",
        "GLEW",
        "SDL2",
        "SDL2_image",
        "cbtCore",
    })

    includedirs({
        SRC_DIR .. "/%{prj.name}",
        SRC_DIR .. "/cbtCore"
    })
