################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Drivers/VL53L0/platform/src/vl53l0x_platform.c 

OBJS += \
./APP/Drivers/VL53L0/platform/src/vl53l0x_platform.o 

C_DEPS += \
./APP/Drivers/VL53L0/platform/src/vl53l0x_platform.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Drivers/VL53L0/platform/src/vl53l0x_platform.o: ../APP/Drivers/VL53L0/platform/src/vl53l0x_platform.c APP/Drivers/VL53L0/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0 -I../APP/Drivers/VL53L0/platform/inc -I../APP/Drivers/VL53L0/platform/src -I../APP/Drivers/VL53L0/core/inc -I../APP/Drivers/VL53L0/core/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0/platform/src/vl53l0x_platform.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

