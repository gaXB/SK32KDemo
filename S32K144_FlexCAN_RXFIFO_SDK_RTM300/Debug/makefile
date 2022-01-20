################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 24
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Generated_Code/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include SDK/platform/devices/S32K144/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/power/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/power/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
S32K144_FlexCAN_RXFIFO_SDK_RTM300.elf \

EXECUTABLES_QUOTED += \
"S32K144_FlexCAN_RXFIFO_SDK_RTM300.elf" \

EXECUTABLES_OS_FORMAT += \
S32K144_FlexCAN_RXFIFO_SDK_RTM300.elf \

SECONDARY_SIZE += \
S32K144_FlexCAN_RXFIFO_SDK_RTM300.siz \

SECONDARY_SIZE_QUOTED += \
"S32K144_FlexCAN_RXFIFO_SDK_RTM300.siz" \

SECONDARY_SIZE_OS_FORMAT += \
S32K144_FlexCAN_RXFIFO_SDK_RTM300.siz \


# All Target
all: warning-messages explicit-dependencies S32K144_FlexCAN_RXFIFO_SDK_RTM300.elf secondary-outputs

# Tool invocations
S32K144_FlexCAN_RXFIFO_SDK_RTM300.elf: $(OBJS) C:/Users/Administrator/Desktop/delet/S32KTEST/S32K144_FlexCAN_RXFIFO_SDK_RTM300/Project_Settings/Linker_Files/S32K144_64_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #25 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "S32K144_FlexCAN_RXFIFO_SDK_RTM300.elf" "@S32K144_FlexCAN_RXFIFO_SDK_RTM300.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

S32K144_FlexCAN_RXFIFO_SDK_RTM300.siz: $(EXECUTABLES)
	@echo 'Executing target #26 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*.d ./*/*/*/*.d ./*/*/*/*/*/*.d ./*/*/*/*/*/*/*.d  ./*/*.o ./*/*/*/*.o ./*/*/*/*/*/*.o ./*/*/*/*/*/*/*.o ./*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

