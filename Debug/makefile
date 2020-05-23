################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/lukes-code/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
guitar-actuator-board.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
guitar-actuator-board.list \


# All Target
all: guitar-actuator-board.elf secondary-outputs

# Tool invocations
guitar-actuator-board.elf: $(OBJS) $(USER_OBJS) C:\Users\Shane\ Farritor\Documents\workspace_1.0.2\workspace_1.0.2\guitar-actuator-board\STM32F030F4PX_FLASH.ld
	arm-none-eabi-gcc -o "guitar-actuator-board.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\Shane Farritor\Documents\workspace_1.0.2\workspace_1.0.2\guitar-actuator-board\STM32F030F4PX_FLASH.ld" --specs=nosys.specs -Wl,-Map="guitar-actuator-board.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

guitar-actuator-board.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "guitar-actuator-board.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
