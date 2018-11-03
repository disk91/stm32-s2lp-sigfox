################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include ItSdk/Src/stm32l_sdk/wdg/subdir.mk
-include ItSdk/Src/stm32l_sdk/rtc/subdir.mk
-include ItSdk/Src/stm32l_sdk/lowpower/subdir.mk
-include ItSdk/Src/stm32l_sdk/eeprom/subdir.mk
-include ItSdk/Src/stm32l_sdk/adc/subdir.mk
-include ItSdk/Src/stm32l_sdk/subdir.mk
-include ItSdk/Src/it_sdk/time/subdir.mk
-include ItSdk/Src/it_sdk/statemachine/subdir.mk
-include ItSdk/Src/it_sdk/sched/subdir.mk
-include ItSdk/Src/it_sdk/lowpower/subdir.mk
-include ItSdk/Src/it_sdk/logger/subdir.mk
-include ItSdk/Src/it_sdk/eeprom/subdir.mk
-include ItSdk/Src/it_sdk/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STM32_Sigfox_ItSdk.elf

# Tool invocations
STM32_Sigfox_ItSdk.elf: $(OBJS) $(USER_OBJS) ../STM32L053R8Tx_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -specs=nosys.specs -specs=nano.specs -T"../STM32L053R8Tx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "STM32_Sigfox_ItSdk.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	arm-none-eabi-objcopy -O ihex "STM32_Sigfox_ItSdk.elf" "STM32_Sigfox_ItSdk.hex"
	arm-none-eabi-size "STM32_Sigfox_ItSdk.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
