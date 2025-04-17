cmake_minimum_required(VERSION 3.10)

project(FPGA_Router)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Custom Build Variant
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel;TADebug")

# Compilation flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_TADEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Ofast")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2")

if (CMAKE_BUILD_TYPE STREQUAL "TADEBUG")
    message(STATUS "Building in Time Attack DEBUG mode")
elseif (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    message(STATUS "Building in Vanilla DEBUG mode")
elseif (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
    message(STATUS "Building in RELEASE mode")
endif ()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Source files
set(MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Interface files
file(GLOB_RECURSE INTERFACES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Interfaces/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Interfaces/*.h"
)

# Reader files
file(GLOB_RECURSE READERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Reader/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Reader/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Reader/*.h"
)

# # Router files
# file(GLOB_RECURSE ROUTERS
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/Router/*.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/Router/*.h"
# )

# # Exporter files
# file(GLOB_RECURSE EXPORTERS
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/Exporter/*.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/Exporter/*.h"
# )

# Create executable
add_executable(${PROJECT_NAME} ${MAIN} ${INTERFACES} ${READERS})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# project(FPGARouter2)
# add_executable(${PROJECT_NAME} src/main2.cpp)