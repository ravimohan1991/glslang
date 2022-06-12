# CAUTION: HIGHLY GENERIC CMAKE BUILD. ALERT ALWAYS!

# Set the project name and version
project(GlSlang VERSION 1.0)

add_compile_definitions(ENABLE_HLSL)

# Adding multiple source files

# Common code files

if(WIN32)
list(APPEND COMMONC glslang/OSDependent/Windows/ossource.cpp)
else(UNIX)
list(APPEND COMMONC glslang/OSDependent/Unix/ossource.cpp)
endif()
list(APPEND COMMONC glslang/GenericCodeGen/CodeGen.cpp glslang/GenericCodeGen/Link.cpp
	glslang/MachineIndependent/glslang.m4 glslang/MachineIndependent/glslang.y
	OGLCompilersDLL/InitializeDll.cpp glslang/CInterface/glslang_c_interface.cpp)
file(GLOB_RECURSE MACHINEINDEPENDENTC glslang/MachineIndependent/*.cpp)
file(GLOB_RECURSE SPIRVC SPIRV/*.cpp)
file(GLOB HLSLC glslang/HLSL/*.cpp)


file(GLOB_RECURSE MACHINEINDEPENDENTH glslang/MachineIndependent/*.h)
file(GLOB_RECURSE SPIRVH SPIRV/*.h)
file(GLOB HLSLH glslang/HLSL/*.h)
list(APPEND COMMONH glslang/OSDependent/osinclude.h OGLCompilersDLL/InitializeDll.h)

# Building the project (STATIC or DYNAMIC (SHARED))
if (BUILD_SHARED_LIBS)
    add_library(GlSlang SHARED ${COMMONC} ${MACHINEINDEPENDENTC} ${SPIRVC} ${HLSLC}
		${COMMONH} ${MACHINEINDEPENDENTH} ${SPIRVH} ${HLSLH}
	)
else()
    add_library(GlSlang STATIC ${COMMONC} ${MACHINEINDEPENDENTC} ${SPIRVC} ${HLSLC}
		${COMMONH} ${MACHINEINDEPENDENTH} ${SPIRVH} ${HLSLH}
		)
endif()

# INTERFACE (Something that Consumers require but Producers don't)
# Since I am a library coder here, I am the Producer
# Rest of the Engine is Consumer here

target_include_directories(GlSlang
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/glslang/include
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(GlSlang PUBLIC GlSlang)
