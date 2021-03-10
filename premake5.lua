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