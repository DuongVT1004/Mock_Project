################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fan_processing/fan.c 

OBJS += \
./fan_processing/fan.o 

C_DEPS += \
./fan_processing/fan.d 


# Each subdirectory must supply rules for building sources it contributes
fan_processing/%.o: ../fan_processing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@fan_processing/fan.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


