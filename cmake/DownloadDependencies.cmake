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

# Create explicit custom targets for each download with stamp files as evidence of completion
FetchContent_GetProperties(benchmarks)
if(benchmarks_POPULATED)
  add_custom_target(download_benchmarks 
    DEPENDS ${benchmarks_SOURCE_DIR}
    COMMENT "Ensure benchmarks are downloaded"
  )
endif()

FetchContent_GetProperties(device_files)
if(device_files_POPULATED)
  add_custom_target(download_device_files
    DEPENDS ${device_files_SOURCE_DIR}
    COMMENT "Ensure device files are downloaded"
  )
endif()

FetchContent_GetProperties(eval_tool)
if(eval_tool_POPULATED)
  if(WIN32)
    add_custom_target(download_eval_tool
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/eval.exe
      COMMENT "Ensure evaluation tool is downloaded"
    )
  else()
    add_custom_target(download_eval_tool
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/eval
      COMMENT "Ensure evaluation tool is downloaded"
    )
  endif()
endif()

# Create setup target that depends on these download targets
add_custom_target(setup 
  DEPENDS download_benchmarks download_device_files download_eval_tool
  COMMENT "Setup completed - all dependencies downloaded"
) 