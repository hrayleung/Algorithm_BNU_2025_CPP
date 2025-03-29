cmake_minimum_required(VERSION 3.10)
project(Algorithm_BNU_2025_CPP)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 解决MacOS头文件问题
if(APPLE)
    # 指定MacOS SDK路径
    execute_process(
            COMMAND xcrun --show-sdk-path
            OUTPUT_VARIABLE MACOS_SDK_PATH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(CMAKE_OSX_SYSROOT ${MACOS_SDK_PATH})

    # 添加所有可能的C++头文件路径
    include_directories(
            ${MACOS_SDK_PATH}/usr/include
            ${MACOS_SDK_PATH}/usr/include/c++/v1
            /usr/local/include
            /opt/homebrew/include
    )
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
            add_executable(${TARGET_NAME} ${SOURCE_FILE}
                    lab01/lab0102.cpp)
        endforeach()
    endif()
endforeach()

# 显示配置信息
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "MacOS SDK path: ${MACOS_SDK_PATH}")
