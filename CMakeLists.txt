cmake_minimum_required(VERSION 3.10)
project(Algorithm_BNU_2025_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenMP 包
if (APPLE)
    set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
    set(OpenMP_C_LIB_NAMES "omp")
    set(OpenMP_CXX_LIB_NAMES "omp")

    if (EXISTS "/opt/homebrew/opt/libomp")
        # Apple Silicon (M1/M2) Mac
        set(OpenMP_C_INCLUDE_DIR "/opt/homebrew/opt/libomp/include")
        set(OpenMP_CXX_INCLUDE_DIR "/opt/homebrew/opt/libomp/include")
        set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
    elseif (EXISTS "/usr/local/opt/libomp")
        # Intel Mac
        set(OpenMP_C_INCLUDE_DIR "/usr/local/opt/libomp/include")
        set(OpenMP_CXX_INCLUDE_DIR "/usr/local/opt/libomp/include")
        set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.dylib")
    else ()
        message(WARNING "libomp not found. Please install with: brew install libomp")
    endif ()

    execute_process(
            COMMAND xcrun --show-sdk-path
            OUTPUT_VARIABLE MACOS_SDK_PATH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(CMAKE_OSX_SYSROOT ${MACOS_SDK_PATH})

    include_directories(
            ${MACOS_SDK_PATH}/usr/include
            ${MACOS_SDK_PATH}/usr/include/c++/v1
            /usr/local/include
            /opt/homebrew/include
            ${OpenMP_CXX_INCLUDE_DIR}
    )
endif ()

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found: ${OpenMP_CXX_VERSION}")
else ()
    message(WARNING "OpenMP not found. Some features may be disabled.")
endif ()

# 自动查找所有 lab 和 notes 目录下的 cpp 文件
file(GLOB_RECURSE ALL_CPP
    lab*/lab*.cpp
    notes_*/**.cpp
)

foreach(src ${ALL_CPP})
    get_filename_component(target ${src} NAME_WE)
    add_executable(${target} ${src})
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${target} PRIVATE OpenMP::OpenMP_CXX)
    endif()
endforeach()

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "MacOS SDK path: ${MACOS_SDK_PATH}")
if (OpenMP_CXX_FOUND)
    message(STATUS "OpenMP libraries: ${OpenMP_CXX_LIBRARIES}")
    message(STATUS "OpenMP flags: ${OpenMP_CXX_FLAGS}")
endif ()
