################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Timer1/subdir.mk
-include Stepper/subdir.mk
-include StepRamp/subdir.mk
-include KiwiDriverV2/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Kiwi2WheeledAccel.lss \

FLASH_IMAGE += \
Kiwi2WheeledAccel.hex \

EEPROM_IMAGE += \
Kiwi2WheeledAccel.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Kiwi2WheeledAccel.elf secondary-outputs

# Tool invocations
Kiwi2WheeledAccel.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,Kiwi2WheeledAccel.map,--cref -mrelax -Wl,--gc-sections -mmcu=atmega32 -o "Kiwi2WheeledAccel.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Kiwi2WheeledAccel.lss: Kiwi2WheeledAccel.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Kiwi2WheeledAccel.elf  >"Kiwi2WheeledAccel.lss"
	@echo 'Finished building: $@'
	@echo ' '

Kiwi2WheeledAccel.hex: Kiwi2WheeledAccel.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Kiwi2WheeledAccel.elf  "Kiwi2WheeledAccel.hex"
	@echo 'Finished building: $@'
	@echo ' '

Kiwi2WheeledAccel.eep: Kiwi2WheeledAccel.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Kiwi2WheeledAccel.elf  "Kiwi2WheeledAccel.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Kiwi2WheeledAccel.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Kiwi2WheeledAccel.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) Kiwi2WheeledAccel.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
