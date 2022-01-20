################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 12
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include src/drivers/subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Bootloader_b11.elf \

EXECUTABLES_QUOTED += \
"Bootloader_b11.elf" \

EXECUTABLES_OS_FORMAT += \
Bootloader_b11.elf \

SECONDARY_FLASH += \
Bootloader_b11.srec \

SECONDARY_FLASH_QUOTED += \
"Bootloader_b11.srec" \

SECONDARY_FLASH_OS_FORMAT += \
Bootloader_b11.srec \

SECONDARY_SIZE += \
Bootloader_b11.siz \

SECONDARY_SIZE_QUOTED += \
"Bootloader_b11.siz" \

SECONDARY_SIZE_OS_FORMAT += \
Bootloader_b11.siz \


# All Target
all: warning-messages explicit-dependencies Bootloader_b11.elf secondary-outputs

# Tool invocations
Bootloader_b11.elf: $(OBJS) C:/Users/liemvt3/workspaceS32DS.ARM.2018.R1/Bootloader_b11/Project_Settings/Linker_Files/S32K144_64_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #13 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "Bootloader_b11.elf" "@Bootloader_b11.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

Bootloader_b11.srec: $(EXECUTABLES)
	@echo 'Executing target #14 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O srec $(EXECUTABLES)  "Bootloader_b11.srec"
	@echo 'Finished building: $@'
	@echo ' '

Bootloader_b11.siz: $(EXECUTABLES)
	@echo 'Executing target #15 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH_QUOTED) ./*/*.d ./*/*/*.d  ./*/*.o ./*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

