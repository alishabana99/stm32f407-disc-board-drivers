################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO/gpio.c 

OBJS += \
./GPIO/gpio.o 

C_DEPS += \
./GPIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
GPIO/%.o GPIO/%.su: ../GPIO/%.c GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_BSP/Lib" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_BSP/Inc" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_BSP/Inc/GPIO" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GPIO

clean-GPIO:
	-$(RM) ./GPIO/gpio.d ./GPIO/gpio.o ./GPIO/gpio.su

.PHONY: clean-GPIO

