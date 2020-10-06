dependenciesDir = "dependencies"
srcDir = "src"
workspaceDir = "workspace"
projectDir = "%{wks.location}/%{prj.name}"
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace("CBTEngine")
    location(workspaceDir)
    architecture("x86_64")
    configurations({"Debug", "Release"})
    startproject("CBTGame")

    --buildoptions({"/permissive-"})

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

project("CBTCore")
    location(projectDir)
    language("C++")
    kind("StaticLib")

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    files({
        srcDir .. "/%{prj.name}/**.h",
        srcDir .. "/%{prj.name}/**.c",
        srcDir .. "/%{prj.name}/**.hpp",
        srcDir .. "/%{prj.name}/**.cpp",
    })

    defines({
        "GLEW_STATIC",
    })

    libdirs({
        dependenciesDir .. "/SDL/lib/**",
        dependenciesDir .. "/GLEW/lib/",
    })

    links({
        "opengl32",
        "glew32s",
        "SDL2",
        "SDL2_image",
    })

    includedirs({
        srcDir .. "/%{prj.name}",

        dependenciesDir .. "/SDL/include",
        dependenciesDir .. "/GLEW/include",
    })

project("CBTGame")
    location(projectDir)
    language("C++")
    kind("ConsoleApp")

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    files({
        srcDir .. "/%{prj.name}/**.h",
        srcDir .. "/%{prj.name}/**.c",
        srcDir .. "/%{prj.name}/**.hpp",
        srcDir .. "/%{prj.name}/**.cpp",
    })

    links({
        "CBTCore"
    })

    includedirs({
        srcDir .. "/%{prj.name}",

        srcDir .. "/CBTCore"
    })

    postbuildcommands({
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/SDL2.dll %{cfg.targetdir}",
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/SDL2_image.dll %{cfg.targetdir}",
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/libtiff-5.dll %{cfg.targetdir}",
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/libwebp-7.dll %{cfg.targetdir}",
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/libjpeg-9.dll %{cfg.targetdir}",
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/libpng16-16.dll %{cfg.targetdir}",
        "{COPY} ../../" .. dependenciesDir .. "/SDL/lib/win64/zlib1.dll %{cfg.targetdir}",
    })
