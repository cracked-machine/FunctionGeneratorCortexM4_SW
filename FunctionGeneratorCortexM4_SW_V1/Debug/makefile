################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include WaveTableGeneration/subdir.mk
-include ILI9341/subdir.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/SIgnalManager/subdir.mk
-include Core/Src/EventManager/subdir.mk
-include Core/Src/DisplayManager/subdir.mk
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
FunctionGeneratorCortexM4_SW_V1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
FunctionGeneratorCortexM4_SW_V1.list \

OBJCOPY_BIN += \
FunctionGeneratorCortexM4_SW_V1.bin \


# All Target
all: FunctionGeneratorCortexM4_SW_V1.elf secondary-outputs

# Tool invocations
FunctionGeneratorCortexM4_SW_V1.elf: $(OBJS) $(USER_OBJS) /home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/STM32G474RETX_FLASH.ld
	arm-none-eabi-gcc -o "FunctionGeneratorCortexM4_SW_V1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/chris/Projects/Embedded/FunctionGeneratorCortexM4_SW/FunctionGeneratorCortexM4_SW_V1/STM32G474RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="FunctionGeneratorCortexM4_SW_V1.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

FunctionGeneratorCortexM4_SW_V1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "FunctionGeneratorCortexM4_SW_V1.list"
	@echo 'Finished building: $@'
	@echo ' '

FunctionGeneratorCortexM4_SW_V1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "FunctionGeneratorCortexM4_SW_V1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
