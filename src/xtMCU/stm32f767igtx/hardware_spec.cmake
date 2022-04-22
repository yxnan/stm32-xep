# STM32F767IGTx 硬件配置

# MCU核心设置
set(MCPU cortex-m7)

# 浮点运算配置
# Uncomment for hardware floating point
# add_compile_definitions(ARM_MATH_CM7;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv5-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv5-d16)

# Uncomment for software floating point
# add_compile_options(-mfloat-abi=soft)

# HAL/FreeRTOS库配置
add_definitions(-DUSE_HAL_DRIVER -DSTM32F767xx)
set(CMSIS_DEVICE STM32F7xx)
set(HAL_DRIVER STM32F7xx_HAL_Driver)
set(ARM_VERSION ARM_CM7)

# 链接脚本/静态库
set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/xtMCU/${HW_PLATFORM}/STM32F767IGTx_FLASH.ld)

# 添加编译原文件
set(HAL_INCLUDE
        xtMCU/${HW_PLATFORM}
        xtMCU/${HW_PLATFORM}/LowLevel
        xtMCU/${HW_PLATFORM}/Drivers/CMSIS/Include
        xtMCU/${HW_PLATFORM}/Drivers/CMSIS/Device/ST/${CMSIS_DEVICE}/Include
        xtMCU/${HW_PLATFORM}/Drivers/${HAL_DRIVER}/Inc
        xtMCU/${HW_PLATFORM}/Drivers/${HAL_DRIVER}/Inc/Legacy
        xtMCU/${HW_PLATFORM}/XEP_HAL
        )

file(GLOB HAL_SRC
        "xtMCU/${HW_PLATFORM}/*.*"
        "xtMCU/${HW_PLATFORM}/FreeRTOS/*.*"
        "xtMCU/${HW_PLATFORM}/LowLevel/*.*"
        "xtMCU/${HW_PLATFORM}/Drivers/${HAL_DRIVER}/Src/*.*"
        "xtMCU/${HW_PLATFORM}/Drivers/${HAL_DRIVER}/Src/Legacy/*.*"
        "xtMCU/${HW_PLATFORM}/XEP_HAL/*.*"
        )
list(FILTER HAL_SRC EXCLUDE REGEX "template.c" )

# 链接库文件
# link_directories(
#         xtMCU/${HW_PLATFORM}
#         xtMCU/${HW_PLATFORM}/Drivers/CMSIS/Lib/GCC
#         )
