cmake_minimum_required(VERSION 3.10)

project(FPGA_Router)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(fpga_router ${MAIN} ${INTERFACES} ${READERS})

# Set output directory
set_target_properties(fpga_router PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Optionally, specify which folders are included in the build
# target_include_directories(fpga_router PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/Interfaces
# )

# project(FPGARouter2)
# add_executable(${PROJECT_NAME} src/main2.cpp)