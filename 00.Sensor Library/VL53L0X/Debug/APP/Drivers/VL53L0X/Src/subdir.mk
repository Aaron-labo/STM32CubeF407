################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Drivers/VL53L0X/Src/ST_I2C.c \
../APP/Drivers/VL53L0X/Src/VL53l0x_i2c_dev.c \
../APP/Drivers/VL53L0X/Src/vl53l0x_api.c \
../APP/Drivers/VL53L0X/Src/vl53l0x_api_calibration.c \
../APP/Drivers/VL53L0X/Src/vl53l0x_api_core.c \
../APP/Drivers/VL53L0X/Src/vl53l0x_api_ranging.c \
../APP/Drivers/VL53L0X/Src/vl53l0x_api_strings.c 

OBJS += \
./APP/Drivers/VL53L0X/Src/ST_I2C.o \
./APP/Drivers/VL53L0X/Src/VL53l0x_i2c_dev.o \
./APP/Drivers/VL53L0X/Src/vl53l0x_api.o \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_calibration.o \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_core.o \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_ranging.o \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_strings.o 

C_DEPS += \
./APP/Drivers/VL53L0X/Src/ST_I2C.d \
./APP/Drivers/VL53L0X/Src/VL53l0x_i2c_dev.d \
./APP/Drivers/VL53L0X/Src/vl53l0x_api.d \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_calibration.d \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_core.d \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_ranging.d \
./APP/Drivers/VL53L0X/Src/vl53l0x_api_strings.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Drivers/VL53L0X/Src/ST_I2C.o: ../APP/Drivers/VL53L0X/Src/ST_I2C.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/ST_I2C.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L0X/Src/VL53l0x_i2c_dev.o: ../APP/Drivers/VL53L0X/Src/VL53l0x_i2c_dev.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/VL53l0x_i2c_dev.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L0X/Src/vl53l0x_api.o: ../APP/Drivers/VL53L0X/Src/vl53l0x_api.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/vl53l0x_api.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L0X/Src/vl53l0x_api_calibration.o: ../APP/Drivers/VL53L0X/Src/vl53l0x_api_calibration.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/vl53l0x_api_calibration.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L0X/Src/vl53l0x_api_core.o: ../APP/Drivers/VL53L0X/Src/vl53l0x_api_core.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/vl53l0x_api_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L0X/Src/vl53l0x_api_ranging.o: ../APP/Drivers/VL53L0X/Src/vl53l0x_api_ranging.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/vl53l0x_api_ranging.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
APP/Drivers/VL53L0X/Src/vl53l0x_api_strings.o: ../APP/Drivers/VL53L0X/Src/vl53l0x_api_strings.c APP/Drivers/VL53L0X/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/VL53L0X/Inc -I../APP/Drivers/VL53L0X/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/VL53L0X/Src/vl53l0x_api_strings.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

