# Download test data and evaluator
include(FetchContent)

message(STATUS "Downloading and setting up project files...")

# Download benchmarks
FetchContent_Declare(
  benchmarks
  URL https://github.com/ippan-kaishain/CENG4120-2025-Final/releases/download/Released/benchmarks.tar.bz2
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks
)

# Download device files
FetchContent_Declare(
  device_files
  URL https://github.com/ippan-kaishain/CENG4120-2025-Final/releases/download/Released/xcvu3p.tar.bz2
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/device
)

# Download evaluation tool
if(WIN32)
  set(EVAL_EXE_NAME "eval.exe")
else()
  set(EVAL_EXE_NAME "eval")
endif()

FetchContent_Declare(
  eval_tool
  URL https://github.com/ippan-kaishain/CENG4120-2025-Final/releases/download/Released/eval
  DOWNLOAD_NO_EXTRACT TRUE
  DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}
)

# Make files available for the build
FetchContent_MakeAvailable(benchmarks device_files eval_tool)

# Make eval executable on Unix platforms
if(UNIX)
  execute_process(
    COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/eval
  )
endif()

# Create setup target that depends on these downloads
add_custom_target(setup DEPENDS benchmarks device_files eval_tool) 