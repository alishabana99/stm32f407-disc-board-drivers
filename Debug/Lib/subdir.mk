################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/common_lib.c 

OBJS += \
./Lib/common_lib.o 

C_DEPS += \
./Lib/common_lib.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/Lib" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/Inc" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/GPIO" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/RCC" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/HAL" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/HAL/LCD" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/SYSTICK" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/USART" -I"D:/THINGS/freeBooks/Programming/Embedded Systems/DataSheets & DOCS/ARM-v7 & Cortex-M/Stm32f407 discovery - ISRAEL GBATI/FLORIDA_STM32_POV/MCAL/ADC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/common_lib.d ./Lib/common_lib.o ./Lib/common_lib.su

.PHONY: clean-Lib

