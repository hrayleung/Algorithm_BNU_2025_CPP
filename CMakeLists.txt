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

# 自动查找所有lab目录并添加
file(GLOB LAB_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "lab*")

foreach(LAB_DIR ${LAB_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LAB_DIR})
        message(STATUS "Found lab directory: ${LAB_DIR}")

        # 查找该lab目录中的所有CPP文件
        file(GLOB LAB_SOURCES "${LAB_DIR}/*.cpp")

        # 为每个CPP文件创建可执行文件
        foreach(SOURCE_FILE ${LAB_SOURCES})
            get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
            set(TARGET_NAME "${LAB_DIR}_${FILE_NAME}")

            message(STATUS "Adding executable: ${TARGET_NAME} from ${SOURCE_FILE}")
            # 只添加一个源文件而不是全部
            add_executable(${TARGET_NAME} ${SOURCE_FILE}
                    lab01/lab0104.cpp)

            # 为每个目标链接 OpenMP (如果找到)
            if(OpenMP_CXX_FOUND)
                target_link_libraries(${TARGET_NAME} PRIVATE OpenMP::OpenMP_CXX)
            endif()
        endforeach()
    endif()
endforeach()

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "MacOS SDK path: ${MACOS_SDK_PATH}")
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP libraries: ${OpenMP_CXX_LIBRARIES}")
    message(STATUS "OpenMP flags: ${OpenMP_CXX_FLAGS}")
endif()
