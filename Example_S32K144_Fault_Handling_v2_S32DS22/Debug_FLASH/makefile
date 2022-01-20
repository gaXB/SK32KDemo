################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 5
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
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
Example_S32K144_Fault_Handling_v2_S32DS22.elf \

EXECUTABLES_QUOTED += \
"Example_S32K144_Fault_Handling_v2_S32DS22.elf" \

EXECUTABLES_OS_FORMAT += \
Example_S32K144_Fault_Handling_v2_S32DS22.elf \

SECONDARY_SIZE += \
Example_S32K144_Fault_Handling_v2_S32DS22.siz \

SECONDARY_SIZE_QUOTED += \
"Example_S32K144_Fault_Handling_v2_S32DS22.siz" \

SECONDARY_SIZE_OS_FORMAT += \
Example_S32K144_Fault_Handling_v2_S32DS22.siz \


# All Target
all: warning-messages explicit-dependencies Example_S32K144_Fault_Handling_v2_S32DS22.elf secondary-outputs

# Tool invocations
Example_S32K144_Fault_Handling_v2_S32DS22.elf: $(OBJS) C:/Users/Administrator/Desktop/Example_S32K144_Fault_Handling_v2_S32DS22/Project_Settings/Linker_Files/S32K144_64_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #6 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "Example_S32K144_Fault_Handling_v2_S32DS22.elf" "@Example_S32K144_Fault_Handling_v2_S32DS22.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

Example_S32K144_Fault_Handling_v2_S32DS22.siz: $(EXECUTABLES)
	@echo 'Executing target #7 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*.d ./*/*/*.d  ./*/*.o ./*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

