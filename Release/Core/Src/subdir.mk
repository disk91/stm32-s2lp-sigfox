################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/gpio.c \
../Core/Src/iwdg.c \
../Core/Src/main.c \
../Core/Src/rtc.c \
../Core/Src/spi.c \
../Core/Src/stm32l0xx_hal_msp.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/system_stm32l0xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/gpio.o \
./Core/Src/iwdg.o \
./Core/Src/main.o \
./Core/Src/rtc.o \
./Core/Src/spi.o \
./Core/Src/stm32l0xx_hal_msp.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/system_stm32l0xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/gpio.d \
./Core/Src/iwdg.d \
./Core/Src/main.d \
./Core/Src/rtc.d \
./Core/Src/spi.d \
./Core/Src/stm32l0xx_hal_msp.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/system_stm32l0xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L053xx -I"C:/Users/paul/Documents/STM32/STM32_Sigfox_ItSdk/Core/Inc" -I"C:/Users/paul/Documents/STM32/STM32_Sigfox_ItSdk/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/paul/Documents/STM32/STM32_Sigfox_ItSdk/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/paul/Documents/STM32/STM32_Sigfox_ItSdk/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/paul/Documents/STM32/STM32_Sigfox_ItSdk/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


