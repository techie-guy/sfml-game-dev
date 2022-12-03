workspace "sfml-game-dev"
  configurations { "debug", "release" }

  postbuildcommands {
    "cp -r assets %{cfg.targetdir}"
  }

project "sfml-game-dev"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "bin/%{cfg.buildcfg}"
  objdir "bin/%{cfg.buildcfg}"
  targetname "game"

  links { "sfml-graphics", "sfml-window", "sfml-system" }

  includedirs { "include" }

  files {
    "src/**.h",
    "src/**.hpp",
    "src/**.cpp",
  }

  filter "configurations:debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:release"
    defines { "NDEBUG" }
    optimize "On"
