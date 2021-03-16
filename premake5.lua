-- premake5.lua
project "OSDependent"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glslang/OSDependent/osinclude.h"
	}


	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

		files
		{
			"glslang/OSDependent/Windows/ossource.cpp"
		}

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

		files
		{
			"glslang/OSDependent/Unix/ossource.cpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "GenericCodeGen"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glslang/GenericCodeGen/CodeGen.cpp",
		"glslang/GenericCodeGen/Link.cpp"
	}


	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

		files
		{
			"glslang/OSDependent/Windows/ossource.cpp"
		}

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

		files
		{
			"glslang/OSDependent/Unix/ossource.cpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "MachineIndependent"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glslang/MachineIndependent/glslang.m4",
		"glslang/MachineIndependent/glslang.y",
		"glslang/MachineIndependent/glslang_tab.cpp",
		"glslang/MachineIndependent/attribute.cpp",
		"glslang/MachineIndependent/Constant.cpp",
		"glslang/MachineIndependent/iomapper.cpp",
		"glslang/MachineIndependent/InfoSink.cpp",
		"glslang/MachineIndependent/Initialize.cpp",
		"glslang/MachineIndependent/IntermTraverse.cpp",
		"glslang/MachineIndependent/Intermediate.cpp",
		"glslang/MachineIndependent/ParseContextBase.cpp",
		"glslang/MachineIndependent/ParseHelper.cpp",
		"glslang/MachineIndependent/PoolAlloc.cpp",
		"glslang/MachineIndependent/RemoveTree.cpp",
		"glslang/MachineIndependent/Scan.cpp",
		"glslang/MachineIndependent/ShaderLang.cpp",
		"glslang/MachineIndependent/SymbolTable.cpp",
		"glslang/MachineIndependent/Versions.cpp",
		"glslang/MachineIndependent/intermOut.cpp",
		"glslang/MachineIndependent/limits.cpp",
		"glslang/MachineIndependent/linkValidate.cpp",
		"glslang/MachineIndependent/parseConst.cpp",
		"glslang/MachineIndependent/reflection.cpp",
		"glslang/MachineIndependent/preprocessor/Pp.cpp",
		"glslang/MachineIndependent/preprocessor/PpAtom.cpp",
		"glslang/MachineIndependent/preprocessor/PpContext.cpp",
		"glslang/MachineIndependent/preprocessor/PpScanner.cpp",
		"glslang/MachineIndependent/preprocessor/PpTokens.cpp",
		"glslang/MachineIndependent/propagateNoContraction.cpp"
	}

	includedirs
	{
		"../glslang"
	}

	links
	{
		"GenericCodeGen"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

		files
		{
			"glslang/OSDependent/Windows/ossource.cpp"
		}

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

		files
		{
			"glslang/OSDependent/Unix/ossource.cpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"


project "OGLCompiler"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"OGLCompilersDLL/InitializeDLL.h",
		"OGLCompilersDLL/InitializeDLL.cpp"
	}


	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"


project "glslang"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glslang/CInterface/glslang_c_interface.cpp"
	}

	includedirs
	{
		"../glslang",
		"StandAlone"
	}

	links
	{
		"OGLCompiler",
		"OSDependent",
		"MachineIndependent"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "HLSL"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glslang/HLSL/**.h",
		"glslang/HLSL/**.cpp"
	}

	defines
	{
		"ENABLE_HLSL"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "SPIRV"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"SPIRV/GlslangToSpv.cpp",
		"SPIRV/InReadableOrder.cpp",
		"SPIRV/Logger.cpp",
		"SPIRV/SpvBuilder.cpp",
		"SPIRV/SpvPostProcess.cpp",
		"SPIRV/doc.cpp",
		"SPIRV/SpvTools.cpp",
		"SPIRV/disassemble.cpp",
		"SPIRV/CInterface/spirv_c_interface.cpp"
	}

	includedirs
	{
		"../glslang",
		"../SPIRV"
	}


	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

		files
		{
			"glslang/OSDependent/Windows/ossource.cpp"
		}

	filter "system:linux"
		-- https://github.com/premake/premake-core/wiki/pic
		pic "On"
		buildoptions "-std=c++11"
		systemversion "latest"

		files
		{
			"glslang/OSDependent/Unix/ossource.cpp"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
