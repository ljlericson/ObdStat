cmake_minimum_required(VERSION 3.30)

# Vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(ObdStat VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Dependencies (from vcpkg) ---
find_package(Boost REQUIRED COMPONENTS asio)
find_package(nlohmann_json CONFIG REQUIRED)

# No C++20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) 

# --- Executable ---
add_executable(ObdStat)

# Sources
file(GLOB_RECURSE OBDSTAT_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

target_sources(ObdStat PRIVATE ${OBDSTAT_SOURCES})

target_link_libraries(ObdStat PRIVATE 
    Boost::asio
    nlohmann_json::nlohmann_json
)

# --- Compiler warnings ---
if(MSVC)
    target_compile_options(ObdStat PRIVATE
        /W3
        /MP
        /WX
        /ZI
    )
else()
    target_compile_options(ObdStat PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# --- Visual Studio niceties ---
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ObdStat)
    set_target_properties(s3glr PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
    )
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${S3GLR_SOURCES})
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()
