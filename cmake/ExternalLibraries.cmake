# External Libraries Configuration
include(FetchContent)

# Set up policy for Boost
if (POLICY CMP0167)
  cmake_policy(SET CMP0167 OLD)
endif()

# ==== Boost Library ====
message(STATUS "Looking for Boost...")
find_package(Boost COMPONENTS iostreams QUIET)

if(NOT Boost_FOUND)
  message(STATUS "Boost not found. Downloading and building...")
  
  # Set Boost version
  set(BOOST_VERSION 1.81.0)
  string(REPLACE "." "_" BOOST_VERSION_UNDERSCORE ${BOOST_VERSION})
  
  # Download Boost
  FetchContent_Declare(
    boost
    URL https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_UNDERSCORE}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  
  # Customize how Boost is fetched to avoid full build
  set(FETCHCONTENT_QUIET OFF)
  FetchContent_GetProperties(boost)
  if(NOT boost_POPULATED)
    message(STATUS "Downloading Boost ${BOOST_VERSION}...")
    FetchContent_Populate(boost)
    
    # Just use the headers (header-only libraries)
    set(Boost_INCLUDE_DIRS ${boost_SOURCE_DIR})
    message(STATUS "Boost downloaded to: ${Boost_INCLUDE_DIRS}")
    
    # For iostreams, we might need to build it
    if(WIN32)
      # Windows - build using b2
      execute_process(
        COMMAND bootstrap.bat
        WORKING_DIRECTORY ${boost_SOURCE_DIR}
      )
      execute_process(
        COMMAND b2 --with-iostreams
        WORKING_DIRECTORY ${boost_SOURCE_DIR}
      )
    else()
      # Unix-like
      execute_process(
        COMMAND ./bootstrap.sh --with-libraries=iostreams
        WORKING_DIRECTORY ${boost_SOURCE_DIR}
      )
      execute_process(
        COMMAND ./b2 --with-iostreams
        WORKING_DIRECTORY ${boost_SOURCE_DIR}
      )
    endif()
    
    # Set libraries path
    set(Boost_LIBRARY_DIRS ${boost_SOURCE_DIR}/stage/lib)
    find_library(Boost_IOSTREAMS_LIBRARY 
      NAMES boost_iostreams
      PATHS ${Boost_LIBRARY_DIRS}
    )
    set(Boost_LIBRARIES ${Boost_IOSTREAMS_LIBRARY})
  endif()
else()
  message(STATUS "Found Boost: ${Boost_INCLUDE_DIRS}")
endif()

# Include Boost directories
include_directories(${Boost_INCLUDE_DIRS})

# ==== OpenMP Library ====
message(STATUS "Looking for OpenMP...")

# Platform-specific OpenMP configuration
if(APPLE)
  # macOS specific OpenMP configuration (Homebrew)
  find_program(BREW_PROGRAM brew)
  
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
  
  # Check if libomp is installed via homebrew
  if(BREW_PROGRAM)
    execute_process(
      COMMAND ${BREW_PROGRAM} --prefix libomp
      OUTPUT_VARIABLE LIBOMP_PREFIX
      OUTPUT_STRIP_TRAILING_WHITESPACE
      RESULT_VARIABLE BREW_RESULT
    )
    
    if(BREW_RESULT EQUAL 0)
      # Found libomp installation
      set(OpenMP_omp_LIBRARY "${LIBOMP_PREFIX}/lib/libomp.dylib")
      include_directories("${LIBOMP_PREFIX}/include")
    else()
      # libomp not installed - prompt user to install it
      message(STATUS "OpenMP not found. On macOS, install with: brew install libomp")
      message(STATUS "Attempting to download a precompiled version...")
      
      # Alternatively, we could download a precompiled version
      # This would be more complex and system-dependent
    endif()
  endif()
  
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