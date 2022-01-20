################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/drivers/clock.c" \
"../src/drivers/comm.c" \
"../src/drivers/fsl_flash_driver_c90tfs.c" \
"../src/drivers/mem_man.c" \
"../src/drivers/pin_config.c" \
"../src/drivers/pit.c" \
"../src/drivers/timeout.c" \
"../src/drivers/uart.c" \

C_SRCS += \
../src/drivers/clock.c \
../src/drivers/comm.c \
../src/drivers/fsl_flash_driver_c90tfs.c \
../src/drivers/mem_man.c \
../src/drivers/pin_config.c \
../src/drivers/pit.c \
../src/drivers/timeout.c \
../src/drivers/uart.c \

C_DEPS_QUOTED += \
"./src/drivers/clock.d" \
"./src/drivers/comm.d" \
"./src/drivers/fsl_flash_driver_c90tfs.d" \
"./src/drivers/mem_man.d" \
"./src/drivers/pin_config.d" \
"./src/drivers/pit.d" \
"./src/drivers/timeout.d" \
"./src/drivers/uart.d" \

OBJS_QUOTED += \
"./src/drivers/clock.o" \
"./src/drivers/comm.o" \
"./src/drivers/fsl_flash_driver_c90tfs.o" \
"./src/drivers/mem_man.o" \
"./src/drivers/pin_config.o" \
"./src/drivers/pit.o" \
"./src/drivers/timeout.o" \
"./src/drivers/uart.o" \

C_DEPS += \
./src/drivers/clock.d \
./src/drivers/comm.d \
./src/drivers/fsl_flash_driver_c90tfs.d \
./src/drivers/mem_man.d \
./src/drivers/pin_config.d \
./src/drivers/pit.d \
./src/drivers/timeout.d \
./src/drivers/uart.d \

OBJS_OS_FORMAT += \
./src/drivers/clock.o \
./src/drivers/comm.o \
./src/drivers/fsl_flash_driver_c90tfs.o \
./src/drivers/mem_man.o \
./src/drivers/pin_config.o \
./src/drivers/pit.o \
./src/drivers/timeout.o \
./src/drivers/uart.o \

OBJS += \
./src/drivers/clock.o \
./src/drivers/comm.o \
./src/drivers/fsl_flash_driver_c90tfs.o \
./src/drivers/mem_man.o \
./src/drivers/pin_config.o \
./src/drivers/pit.o \
./src/drivers/timeout.o \
./src/drivers/uart.o \


# Each subdirectory must supply rules for building sources it contributes
src/drivers/clock.o: ../src/drivers/clock.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/clock.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/clock.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/comm.o: ../src/drivers/comm.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/comm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/comm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/fsl_flash_driver_c90tfs.o: ../src/drivers/fsl_flash_driver_c90tfs.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/fsl_flash_driver_c90tfs.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/fsl_flash_driver_c90tfs.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/mem_man.o: ../src/drivers/mem_man.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/mem_man.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/mem_man.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/pin_config.o: ../src/drivers/pin_config.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/pin_config.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/pin_config.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/pit.o: ../src/drivers/pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/pit.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/pit.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/timeout.o: ../src/drivers/timeout.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/timeout.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/timeout.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/uart.o: ../src/drivers/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/drivers/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/drivers/uart.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


