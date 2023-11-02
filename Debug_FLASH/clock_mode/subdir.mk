################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../clock_mode/clock_mode.c 

OBJS += \
./clock_mode/clock_mode.o 

C_DEPS += \
./clock_mode/clock_mode.d 


# Each subdirectory must supply rules for building sources it contributes
clock_mode/%.o: ../clock_mode/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@clock_mode/clock_mode.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


