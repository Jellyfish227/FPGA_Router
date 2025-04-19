cmake_minimum_required(VERSION 3.14)

project(FPGA_Router)

# Include the dependencies download module
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadDependencies.cmake)

# Include the external libraries module
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ExternalLibraries.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Custom Build Variant
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel;TADebug")

# Compilation flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_TADEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -ffast-math")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2")

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS} # remove if external lib is not allowed
)

# Source files
set(MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Interface files
file(GLOB_RECURSE INTERFACES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Interfaces/*.hpp"
)

# Reader files
file(GLOB_RECURSE READERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Reader/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Reader/*.hpp"
)

# Router files
file(GLOB_RECURSE ROUTERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Router/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Router/*.hpp"
)

# Exporter files
file(GLOB_RECURSE EXPORTERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Exporter/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Exporter/*.hpp"
)

# Create executable
add_executable(${PROJECT_NAME} 
    ${MAIN} 
    ${INTERFACES} 
    ${READERS} 
    ${ROUTERS} 
    ${EXPORTERS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${Boost_LIBRARIES}
    OpenMP::OpenMP_CXX
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# project(FPGARouter2)
# add_executable(${PROJECT_NAME} src/main2.cpp)