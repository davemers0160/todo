# ----------------------------------------------------------------------------
#  Root CMake file for DfD Graph Cuts
# ----------------------------------------------------------------------------
#
# To perform an out of source build do the following on the command line:
# 1. navigate to the root project directory (in this case DfD2)
# 2. mkdir build
# 3. cd build
# 4. depending on your system (windows/linux) type the following
# Example CMake build line for windows & VS2015
# windows: cmake -G "Visual Studio 14 2015 Win64" -DUSE_AVX_INSTRUCTIONS=ON ..
# linux: cmake -DUSE_AVX_INSTRUCTIONS=ON ..
#
# 5. To compile:
# windows: cmake --build . --config Release
# linux: cmake --build . --config Release -- -j10
#

cmake_minimum_required(VERSION 3.9)

#PROJECT(mnist_lib)
project(todo_project VERSION 1.0 DESCRIPTION "Project to create a cross platform todo tracker")
set(CMAKE_CXX_STANDARD 11)

set(exe_name "todo")


if(WIN32)
    # Change these to point to the right location for a particular machine
    #set(DLIB_ROOT "D:/dlib-19.17")
    set(COMMON_ROOT "D:/Common")
    #add_definitions(-DMNIST_DLL_EXPORTS)
	#add_subdirectory(${DLIB_ROOT}/dlib dlib_build)
    
elseif(UNIX)
    # Change these to point to the right location for a particular machine
    set(HOME "$ENV{HOME}" CACHE INTERNAL "Copied from environment variable")
    #set(DLIB_ROOT "${HOME}/dlib-19.18")
    set(COMMON_ROOT "${HOME}/Projects/Common")
    #add_subdirectory(${DLIB_ROOT}/dlib dlib_build)
    
elseif(APPLE)
    message(FATAL_ERROR "Apple -> Not Even!")
    
endif()    


# get the source files for the Library
file(GLOB SOURCES "src/*.cpp")
#set(SOURCES ${SOURCES} "${DLIB_ROOT}/dlib/all/source.cpp")

set(project_includes "include" 
                    "${COMMON_ROOT}/include" 
 #                   ${DLIB_ROOT}
                    )
                    

message(" ")
message("--------------------------------------------------------")
message("Source Files: ")
foreach(S ${SOURCES})
    message("  " ${S})
endforeach()
message("--------------------------------------------------------")
message(" ")

message(" ")
message("--------------------------------------------------------")
message("Project Includes: ")
foreach(S ${project_includes})
    message("  " ${S})
endforeach()
message("--------------------------------------------------------")
message(" ")

include_directories(${project_includes})
add_executable(${exe_name} ${SOURCES})

if(WIN32)
    message("MSVC Version: " ${MSVC_VERSION})
    # uncomment for MSVC and cmake greater than 3.6.0
    set(default_build_type "Release")
    if(MSVC AND (${CMAKE_VERSION} VERSION_GREATER "3.6.0"))
        target_compile_options(${exe_name} PRIVATE "/MP" /arch:AVX)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${exe_name})
    endif()
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
endif()

message(" ")
message(STATUS "Build Complete!")
message(" ")



