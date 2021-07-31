################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Drivers/VL53L1/platform/IOI2C.c \
../APP/Drivers/VL53L1/platform/vl53l1_platform.c \
../APP/Drivers/VL53L1/platform/vl53l1x.c 

OBJS += \
./APP/Drivers/VL53L1/platform/IOI2C.o \
./APP/Drivers/VL53L1/platform/vl53l1_platform.o \
./APP/Drivers/VL53L1/platform/vl53l1x.o 

C_DEPS += \
./APP/Drivers/VL53L1/platform/IOI2C.d \
./APP/Drivers/VL53L1/platform/vl53l1_platform.d \
./APP/Drivers/VL53L1/platform/vl53l1x.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Drivers/VL53L1/platform/IOI2C.o: ../APP/Drivers/VL53L1/platform/IOI2C.c APP/Drivers/VL53L1/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/platform/IOI2C.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/platform/vl53l1_platform.o: ../APP/Drivers/VL53L1/platform/vl53l1_platform.c APP/Drivers/VL53L1/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/platform/vl53l1_platform.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/platform/vl53l1x.o: ../APP/Drivers/VL53L1/platform/vl53l1x.c APP/Drivers/VL53L1/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/platform/vl53l1x.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

