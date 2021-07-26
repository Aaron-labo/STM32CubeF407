################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Drivers/USART_IT/usart_it.c 

OBJS += \
./APP/Drivers/USART_IT/usart_it.o 

C_DEPS += \
./APP/Drivers/USART_IT/usart_it.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Drivers/USART_IT/usart_it.o: ../APP/Drivers/USART_IT/usart_it.c APP/Drivers/USART_IT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../APP/Drivers/USART_IT -I../APP/Inc -I../APP/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"APP/Drivers/USART_IT/usart_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

