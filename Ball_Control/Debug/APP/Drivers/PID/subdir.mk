################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Drivers/PID/PID.c 

OBJS += \
./APP/Drivers/PID/PID.o 

C_DEPS += \
./APP/Drivers/PID/PID.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Drivers/PID/PID.o: ../APP/Drivers/PID/PID.c APP/Drivers/PID/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Inc -I../APP/Src -I../APP/Drivers/LCD -I../APP/Drivers/MPU6050 -I../APP/Drivers/host_computer -I../APP/Drivers/PCA9685 -I../APP/Drivers/PID -I../APP/Drivers/KeyBoard -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/PID/PID.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

