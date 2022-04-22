cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# project settings
project(xep_${HW_PLATFORM} C ASM)

include(xtMCU/${HW_PLATFORM}/hardware_spec.cmake)

add_compile_options(-mcpu=${MCPU} -mthumb)
add_compile_options(-ffunction-sections -fdata-sections)

# Uncomment to mitigate c++17 absolute addresses warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

include_directories(    #[[@EDIT 头文件路径]]
        FreeRTOS/v9.0.0/Source/include
        FreeRTOS/v9.0.0/Source/portable/GCC/${ARM_VERSION}/r0p1

        ${HAL_INCLUDE}

        xtXEP/src
        xtXEP/src/Dispatch
        xtXEP/src/XEPA
        xtXEP/src/System
        xtXEP/src/System/File
        xtXEP/src/HostCom
        xtXEP/src/Radar
        xtXEP/src/XDriver
        xtXEP/src/Tools
        xtXEP/include

        xtSerial/src
        )


file(GLOB_RECURSE XEP_SRC   #[[@EDIT 添加要编译的源文件]]
        "xtSerial/*.*"
        "xtXEP/*.*"
        )
file(GLOB FREERTOS_SRC
        "FreeRTOS/v9.0.0/Source/*.*"
        "FreeRTOS/v9.0.0/Source/portable/GCC/${ARM_VERSION}/r0p1/*.*"
        )
set(ALL_SOURCES ${XEP_SRC} ${HAL_SRC} ${FREERTOS_SRC})

add_link_options(
        -lc -lm -lnosys -specs=nano.specs
        -mcpu=${MCPU} -mthumb
        -T${LINKER_SCRIPT}
        -Wl,-gc-sections
        -Wl,--print-memory-usage
        -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref
        )

add_executable(${PROJECT_NAME}.elf ${ALL_SOURCES})
add_library(${PROJECT_NAME} STATIC ${ALL_SOURCES})

# set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER} <OBJECTS> <LINK_FLAGS> <LINK_LIBRARIES> -o <TARGET>")
# set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINKER_LANGUAGE CXX)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}"
        )