cmake_minimum_required(VERSION 3.15)
project(blinky C ASM)

set(CMAKE_C_STANDARD 11)

set(
    MCU_FLAGS
    "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard"
)
set(
    CMAKE_C_FLAGS
    "${MCU_FLAGS} -DSTM32G491xx -DUSE_HAL_DRIVER -Wall -Werror -Wextra -O0 -g3 -ffunction-sections -fdata-sections"
)
set(
    CMAKE_EXE_LINKER_FLAGS
    "${MCU_FLAGS} -Wl,--gc-sections -T${CMAKE_SOURCE_DIR}/STM32CubeG4/Projects/NUCLEO-G491RE/Templates/STM32CubeIDE/STM32G491RETX_FLASH.ld"
)

include_directories(
    ${CMAKE_SOURCE_DIR}/configs
    ${CMAKE_SOURCE_DIR}/STM32CubeG4/Drivers/CMSIS/Device/ST/STM32G4xx/Include
    ${CMAKE_SOURCE_DIR}/STM32CubeG4/Drivers/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}/STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Inc
)

set(
    SOURCES
    src/main.c
    STM32CubeG4/Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/gcc/startup_stm32g491xx.s
    STM32CubeG4/Drivers/CMSIS/Device/ST/STM32G4xx/Source/Templates/system_stm32g4xx.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
    STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)
