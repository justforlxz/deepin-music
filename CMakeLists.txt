#cmake版本
cmake_minimum_required(VERSION 3.0)

project(music)

#cmake属性
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(USE_DXCB "integration with dxcb platform plugin" OFF)
option(DMR_DEBUG "turn on debug output" off)
option(DTK_DMAN_PORTAL "turn on dman portal support" off)
option(SANITIZER_CHECK "use sanitizer to check memory leak" off)

execute_process(COMMAND uname -m OUTPUT_VARIABLE MACH
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DMR_DEBUG on)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "mips64")
    SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -Wl,-O1 -Wl,--as-needed -fPIE -ffunction-sections -fdata-sections -Wl,--gc-sections -ftree-vectorize -march=loongson3a -mhard-float -mno-micromips -mno-mips16 -flax-vector-conversions -mloongson-ext2 -mloongson-mmi")
    SET(CMAKE_C_FLAGS "$ENV{CFLAGS} -O3 -Wl,-O1 -Wl,--as-needed -fPIE -ffunction-sections -fdata-sections -Wl,--gc-sections -ftree-vectorize -march=loongson3a -mhard-float -mno-micromips -mno-mips16 -flax-vector-conversions -mloongson-ext2 -mloongson-mmi")
    SET(CMAKE_EXE_LINKER_FLAGS  "-pie")
else()
    SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3 -Wl,-O1 -Wl,--as-needed -fPIE -ffunction-sections -fdata-sections -Wl,--gc-sections")
    SET(CMAKE_C_FLAGS "$ENV{CFLAGS} -O3  -Wl,-O1 -Wl,--as-needed -fPIE -ffunction-sections -fdata-sections -Wl,--gc-sections")
    SET(CMAKE_EXE_LINKER_FLAGS  "-pie")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(PkgConfig REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
set(QtModule Core Gui Widgets Multimedia Xml Sql DBus)
#先查找到这些qt相关的模块以供链接使用
find_package(Qt5 REQUIRED ${QtModule})

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h @ONLY)

add_subdirectory(music)
