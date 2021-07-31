################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Drivers/VL53L1/core/vl53l1_api.c \
../APP/Drivers/VL53L1/core/vl53l1_api_calibration.c \
../APP/Drivers/VL53L1/core/vl53l1_api_core.c \
../APP/Drivers/VL53L1/core/vl53l1_api_debug.c \
../APP/Drivers/VL53L1/core/vl53l1_api_preset_modes.c \
../APP/Drivers/VL53L1/core/vl53l1_api_strings.c \
../APP/Drivers/VL53L1/core/vl53l1_core.c \
../APP/Drivers/VL53L1/core/vl53l1_core_support.c \
../APP/Drivers/VL53L1/core/vl53l1_error_strings.c \
../APP/Drivers/VL53L1/core/vl53l1_register_funcs.c \
../APP/Drivers/VL53L1/core/vl53l1_silicon_core.c \
../APP/Drivers/VL53L1/core/vl53l1_wait.c 

OBJS += \
./APP/Drivers/VL53L1/core/vl53l1_api.o \
./APP/Drivers/VL53L1/core/vl53l1_api_calibration.o \
./APP/Drivers/VL53L1/core/vl53l1_api_core.o \
./APP/Drivers/VL53L1/core/vl53l1_api_debug.o \
./APP/Drivers/VL53L1/core/vl53l1_api_preset_modes.o \
./APP/Drivers/VL53L1/core/vl53l1_api_strings.o \
./APP/Drivers/VL53L1/core/vl53l1_core.o \
./APP/Drivers/VL53L1/core/vl53l1_core_support.o \
./APP/Drivers/VL53L1/core/vl53l1_error_strings.o \
./APP/Drivers/VL53L1/core/vl53l1_register_funcs.o \
./APP/Drivers/VL53L1/core/vl53l1_silicon_core.o \
./APP/Drivers/VL53L1/core/vl53l1_wait.o 

C_DEPS += \
./APP/Drivers/VL53L1/core/vl53l1_api.d \
./APP/Drivers/VL53L1/core/vl53l1_api_calibration.d \
./APP/Drivers/VL53L1/core/vl53l1_api_core.d \
./APP/Drivers/VL53L1/core/vl53l1_api_debug.d \
./APP/Drivers/VL53L1/core/vl53l1_api_preset_modes.d \
./APP/Drivers/VL53L1/core/vl53l1_api_strings.d \
./APP/Drivers/VL53L1/core/vl53l1_core.d \
./APP/Drivers/VL53L1/core/vl53l1_core_support.d \
./APP/Drivers/VL53L1/core/vl53l1_error_strings.d \
./APP/Drivers/VL53L1/core/vl53l1_register_funcs.d \
./APP/Drivers/VL53L1/core/vl53l1_silicon_core.d \
./APP/Drivers/VL53L1/core/vl53l1_wait.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Drivers/VL53L1/core/vl53l1_api.o: ../APP/Drivers/VL53L1/core/vl53l1_api.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_api.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_api_calibration.o: ../APP/Drivers/VL53L1/core/vl53l1_api_calibration.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_api_calibration.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_api_core.o: ../APP/Drivers/VL53L1/core/vl53l1_api_core.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_api_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_api_debug.o: ../APP/Drivers/VL53L1/core/vl53l1_api_debug.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_api_debug.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_api_preset_modes.o: ../APP/Drivers/VL53L1/core/vl53l1_api_preset_modes.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_api_preset_modes.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_api_strings.o: ../APP/Drivers/VL53L1/core/vl53l1_api_strings.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_api_strings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_core.o: ../APP/Drivers/VL53L1/core/vl53l1_core.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_core_support.o: ../APP/Drivers/VL53L1/core/vl53l1_core_support.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_core_support.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_error_strings.o: ../APP/Drivers/VL53L1/core/vl53l1_error_strings.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_error_strings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_register_funcs.o: ../APP/Drivers/VL53L1/core/vl53l1_register_funcs.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_register_funcs.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_silicon_core.o: ../APP/Drivers/VL53L1/core/vl53l1_silicon_core.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_silicon_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L1/core/vl53l1_wait.o: ../APP/Drivers/VL53L1/core/vl53l1_wait.c APP/Drivers/VL53L1/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L1/platform -I../APP/Drivers/VL53L1/core -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L1/core/vl53l1_wait.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

