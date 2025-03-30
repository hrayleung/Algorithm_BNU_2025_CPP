cmake_minimum_required(VERSION 3.10)
project(Algorithm_BNU_2025_CPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenMP 包
if(APPLE)
    set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
    set(OpenMP_C_LIB_NAMES "omp")
    set(OpenMP_CXX_LIB_NAMES "omp")

    if(EXISTS "/opt/homebrew/opt/libomp")
        # Apple Silicon (M1/M2) Mac
        set(OpenMP_C_INCLUDE_DIR "/opt/homebrew/opt/libomp/include")
        set(OpenMP_CXX_INCLUDE_DIR "/opt/homebrew/opt/libomp/include")
        set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
    elseif(EXISTS "/usr/local/opt/libomp")
        # Intel Mac
        set(OpenMP_C_INCLUDE_DIR "/usr/local/opt/libomp/include")
        set(OpenMP_CXX_INCLUDE_DIR "/usr/local/opt/libomp/include")
        set(OpenMP_omp_LIBRARY "/usr/local/opt/libomp/lib/libomp.dylib")
    else()
        message(WARNING "libomp not found. Please install with: brew install libomp")
    endif()

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
endif()

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found: ${OpenMP_CXX_VERSION}")
else()
    message(WARNING "OpenMP not found. Some features may be disabled.")
endif()

# 手动添加每个可执行文件

# Lab01 可执行文件
add_executable(lab0101 lab01/lab0101.cpp)
add_executable(lab0102 lab01/lab0102.cpp)
add_executable(lab0103 lab01/lab0103.cpp)
add_executable(lab0104 lab01/lab0104.cpp)

# Lab02 可执行文件
add_executable(lab0201 lab02/lab0201.cpp)
add_executable(lab0202 lab02/lab0202.cpp)

# 为所有目标链接 OpenMP (如果找到)
if(OpenMP_CXX_FOUND)
    target_link_libraries(lab0101 PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(lab0102 PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(lab0103 PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(lab0104 PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(lab0201 PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(lab0202 PRIVATE OpenMP::OpenMP_CXX)
endif()

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "MacOS SDK path: ${MACOS_SDK_PATH}")
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP libraries: ${OpenMP_CXX_LIBRARIES}")
    message(STATUS "OpenMP flags: ${OpenMP_CXX_FLAGS}")
endif()
add_executable(lab0203 lab02/lab0203.cpp)
