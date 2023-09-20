workspace "Pong"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    startproject "Pong"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Pong"