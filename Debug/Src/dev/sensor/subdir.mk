################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dev/sensor/esp8266_dev.c \
../Src/dev/sensor/hc_06.c 

OBJS += \
./Src/dev/sensor/esp8266_dev.o \
./Src/dev/sensor/hc_06.o 

C_DEPS += \
./Src/dev/sensor/esp8266_dev.d \
./Src/dev/sensor/hc_06.d 


# Each subdirectory must supply rules for building sources it contributes
Src/dev/sensor/%.o: ../Src/dev/sensor/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/kdj6724/stm32/test/Inc" -IC:/Users/kdj6724/STM32Cube/Repository/STM32Cube_FW_F1_V1.6.1/Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/kdj6724/STM32Cube/Repository/STM32Cube_FW_F1_V1.6.1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/kdj6724/STM32Cube/Repository/STM32Cube_FW_F1_V1.6.1/Drivers/CMSIS/Device/ST/STM32F1xx/Include -IC:/Users/kdj6724/STM32Cube/Repository/STM32Cube_FW_F1_V1.6.1/Drivers/CMSIS/Include  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


