################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO/gpio.c 

OBJS += \
./MCAL/GPIO/gpio.o 

C_DEPS += \
./MCAL/GPIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPIO/%.o MCAL/GPIO/%.su: ../MCAL/GPIO/%.c MCAL/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/Lib" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/Inc" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/GPIO" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/RCC" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/HAL" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/HAL/LCD" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/SYSTICK" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/USART" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/ADC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-GPIO

clean-MCAL-2f-GPIO:
	-$(RM) ./MCAL/GPIO/gpio.d ./MCAL/GPIO/gpio.o ./MCAL/GPIO/gpio.su

.PHONY: clean-MCAL-2f-GPIO

