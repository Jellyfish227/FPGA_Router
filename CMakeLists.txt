cmake_minimum_required(VERSION 3.10)

project(FPGA_Router)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find external lib begins
if (POLICY CMP0167)
  cmake_policy(SET CMP0167 OLD)
endif()
find_package(Boost REQUIRED COMPONENTS iostreams)

# Platform-specific OpenMP configuration
if(APPLE)
  # macOS specific OpenMP configuration (Homebrew)
  if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
    set(OpenMP_C_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY omp)
  endif()
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
    set(OpenMP_CXX_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY omp)
  endif()
  # Path to libomp installed via Homebrew
  set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
  include_directories("/opt/homebrew/opt/libomp/include")
elseif(WIN32)
  # Windows with MSVC
  if(MSVC)
    set(OpenMP_C_FLAGS "/openmp")
    set(OpenMP_CXX_FLAGS "/openmp")
  endif()
elseif(UNIX AND NOT APPLE)
  # Linux configuration
  # Most Linux compilers support OpenMP out of the box
  # Just ensure the packages are installed:
  # - For Ubuntu/Debian: sudo apt-get install libomp-dev
  # - For Fedora/RHEL: sudo dnf install libomp-devel
endif()

find_package(OpenMP REQUIRED)

# Add compiler flags for OpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# Find external lib ends

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

# Line external lib begin
# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${Boost_LIBRARIES}
    OpenMP::OpenMP_CXX
)
# Line external lib end

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# project(FPGARouter2)
# add_executable(${PROJECT_NAME} src/main2.cpp)