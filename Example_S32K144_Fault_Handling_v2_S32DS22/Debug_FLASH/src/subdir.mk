################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/fault_exceptions.c" \
"../src/main.c" \

C_SRCS += \
../src/fault_exceptions.c \
../src/main.c \

OBJS_OS_FORMAT += \
./src/fault_exceptions.o \
./src/main.o \

C_DEPS_QUOTED += \
"./src/fault_exceptions.d" \
"./src/main.d" \

OBJS += \
./src/fault_exceptions.o \
./src/main.o \

OBJS_QUOTED += \
"./src/fault_exceptions.o" \
"./src/main.o" \

C_DEPS += \
./src/fault_exceptions.d \
./src/main.d \


# Each subdirectory must supply rules for building sources it contributes
src/fault_exceptions.o: ../src/fault_exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/fault_exceptions.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/fault_exceptions.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


