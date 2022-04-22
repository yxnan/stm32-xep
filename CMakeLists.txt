cmake_minimum_required(VERSION 3.17)

# project settings
set(CMAKE_TOOLCHAIN_FILE arm-toolchains.cmake)
set(HW_PLATFORM stm32f767igtx)  #[[@EDIT 硬件平台设置]]

project(xep_toplevel)
add_subdirectory(src)