################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../SDK/platform/devices/S32K144/startup/system_S32K144.c" \

C_SRCS += \
../SDK/platform/devices/S32K144/startup/system_S32K144.c \

OBJS_OS_FORMAT += \
./SDK/platform/devices/S32K144/startup/system_S32K144.o \

C_DEPS_QUOTED += \
"./SDK/platform/devices/S32K144/startup/system_S32K144.d" \

OBJS += \
./SDK/platform/devices/S32K144/startup/system_S32K144.o \

OBJS_QUOTED += \
"./SDK/platform/devices/S32K144/startup/system_S32K144.o" \

C_DEPS += \
./SDK/platform/devices/S32K144/startup/system_S32K144.d \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/devices/S32K144/startup/system_S32K144.o: ../SDK/platform/devices/S32K144/startup/system_S32K144.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/devices/S32K144/startup/system_S32K144.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/devices/S32K144/startup/system_S32K144.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


