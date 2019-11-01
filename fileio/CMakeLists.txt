set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 1)

# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.3)
# 项目信息
project (main)

# Android 5.0 以上需要在此处设置 PIE
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS} -fPIE")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIE -pie")

set(CMAKE_SYSTEM_VERSION 21) # API level
set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)
set(CMAKE_ANDROID_NDK /Users/allstarw.wzl/app/AndroidSDK/ndk-bundle)
set(CMAKE_ANDROID_STL_TYPE gnustl_static)

# 指定生成目标
add_executable(main main.c)
