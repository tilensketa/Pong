workspace "Pong"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    startproject "Pong"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pong"
    location "Pong"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/vendor/glad/src/glad.c"
    }

    includedirs {
        "%{prj.name}/vendor/glad/include",
        "%{prj.name}/vendor/GLFW/include",
        "%{prj.name}/vendor/glm",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/stb"
    }

    libdirs {
        "%{prj.name}/vendor/GLFW/lib-vc2022"
    }

    links {
        "glfw3.lib",
        "opengl32.lib"
    }

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        optimize "on"