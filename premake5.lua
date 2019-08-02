workspace ("gml")
   configurations { "Debug", "OptimizedDebug", "Release" }
   platforms { "x86", "x64" }

SourceDir = "Source/"
BinaryDir = "bin/".._ACTION.."-%{cfg.buildcfg}-%{cfg.platform}"
ObjDir = "binobj/".._ACTION.."-%{cfg.buildcfg}-%{cfg.platform}"

Defines = {}
Defines["C0"] = { "NOMINMAX", "_DEBUG" }
Defines["C1"] = { "NOMINMAX", "NDEBUG" }
Defines["C2"] = { "NOMINMAX", "NDEBUG" }

Symbols = {}
Symbols["C0"] = "On"
Symbols["C1"] = "On"
Symbols["C2"] = "Off"

Optimize = {}
Optimize["C0"] = "Off"
Optimize["C1"] = "Debug"
Optimize["C2"] = "Speed"

Flags = {}
Flags["C0"] = { "NoMinimalRebuild", "MultiProcessorCompile" }
Flags["C1"] = { "NoMinimalRebuild", "MultiProcessorCompile" }
Flags["C2"] = { "NoMinimalRebuild", "MultiProcessorCompile", "LinkTimeOptimization" }
   
project ("gml")
   kind          ("ConsoleApp")
   language      ("C++")
   cppdialect    ("C++17")
   characterset  ("ASCII")
   staticruntime ("on")
   targetdir     (BinaryDir)
   objdir        (ObjDir)
   files         { SourceDir.."**.h", SourceDir.."**.cpp" }
   includedirs   { SourceDir }

   filter { "configurations:Debug" }
      defines  (Defines ["C0"])
      symbols  (Symbols ["C0"])
      optimize (Optimize["C0"])
      flags    (Flags   ["C0"])

   filter { "configurations:OptimizedDebug" }
      defines  (Defines ["C1"])
      symbols  (Symbols ["C1"])
      optimize (Optimize["C1"])
      flags    (Flags   ["C1"])

   filter { "configurations:Release" }
      defines  (Defines ["C2"])
      symbols  (Symbols ["C2"])
      optimize (Optimize["C2"])
      flags    (Flags   ["C2"])
   
   filter { "platforms:x86" }
      architecture ("x86")
      
   filter { "platforms:x64" }
      architecture ("x64")
   